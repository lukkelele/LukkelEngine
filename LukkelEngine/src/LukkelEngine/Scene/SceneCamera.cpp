#include "LKpch.h"
#include "LukkelEngine/Scene/SceneCamera.h"
#include "LukkelEngine/Core/Application.h"


namespace LukkelEngine {

	SceneCamera::SceneCamera(float FOV, float nearPlane, float farPlane)
		: m_FOV(FOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		LKLOG_INFO("FPS Camera created | FOV: {0}", m_FOV);
		const glm::quat orientation = getOrientation();

		m_Yaw = 3.0f * glm::pi<float>() / 4.0f;
		m_Pitch = glm::pi<float>() / 4.0f;

		m_Projection = glm::perspectiveFov(glm::radians(m_FOV), m_ViewportWidth, m_ViewportHeight, m_NearPlane, m_FarPlane);
		m_View = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewProjection = m_Projection * m_View;

		auto mousePos = Mouse::getMousePosition();
		m_InitialMousePos = { mousePos.first, mousePos.second };
	}

	void SceneCamera::updateProjection()
	{
		m_Projection = glm::perspectiveFov(glm::radians(m_FOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearPlane, m_FarPlane);
	}

	void SceneCamera::updateView()
	{
		m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void SceneCamera::updateMousePosition()
	{
		const glm::vec2& mousePos { Mouse::getMouseX(), Mouse::getMouseY() };
		m_MouseDelta = (mousePos - m_MousePos);
		m_MousePos = mousePos;

		if (Keyboard::isKeyPressed(Key::Escape))
			m_MouseEnabled = false;
	}

	glm::vec3 SceneCamera::getUpDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 SceneCamera::getRightDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 SceneCamera::getForwardDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat SceneCamera::getOrientation() const
	{
		return glm::quat(glm::vec3(m_Pitch, m_Yaw, 0.0f));
	}

	glm::vec3 SceneCamera::getDirection()
	{
		glm::vec3 lookAt = m_Position + getForwardDirection();
		m_Direction = glm::normalize(lookAt - m_Position);
		return m_Direction;
	}

	glm::vec3 SceneCamera::calculatePosition() const
	{
		return m_Origin - getForwardDirection() * m_Distance;
	}

	void SceneCamera::onUpdate(float ts)
	{
		hasMouseMoved = false;

		if (m_KeyboardEnabled)
		{
			// WASD
			if (Keyboard::isKeyPressed(Key::W))
				m_Position += m_ForwardDirection * ts * m_TravelSpeed;
			if (Keyboard::isKeyPressed(Key::S))
				m_Position -= m_ForwardDirection * ts * m_TravelSpeed;
			if (Keyboard::isKeyPressed(Key::A))
				m_Position -= m_RightDirection * ts * m_TravelSpeed;
			if (Keyboard::isKeyPressed(Key::D))
				m_Position += m_RightDirection * ts * m_TravelSpeed;
		}

		const float distance = glm::distance(m_Origin, m_Position);
		m_Origin = m_Position + getForwardDirection() * distance;
		m_Distance = distance;
		

		// Release mouse focus
		if (Keyboard::isKeyPressed(Key::Escape))
		{
			if (m_MouseEnabled)
			{
				glfwSetInputMode(Application::get().getWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				m_MouseEnabled = false;
			}
		}
		// Reinstate mouse focus
		else if (Keyboard::isKeyPressed(Key::G))
		{
			if (!m_MouseEnabled)
			{
				// Application::get().getWindow()->setInputLock(true);
				glfwSetInputMode(Application::get().getWindow()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				m_MouseEnabled = true;
			}
		}

		m_RightDirection = glm::cross(m_ForwardDirection, m_UpDirection);
		updateMousePosition();
		// If the mouse has moved since last frame, update camera rotation
		if (m_MouseEnabled)
		{
			if (m_MouseDelta.x != 0.0f || m_MouseDelta.y != 0.0f)
			{
				float yaw = -m_MouseDelta.x * m_RotationSpeed;
				float pitch = -m_MouseDelta.y * m_RotationSpeed;
				m_Yaw = yaw; m_Pitch = pitch;

				glm::quat quat = glm::normalize(glm::cross(glm::angleAxis(pitch, m_RightDirection),
					glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f))));

				m_ForwardDirection = glm::rotate(quat, m_ForwardDirection);
				hasMouseMoved = true;
			}

		}

		updateProjection();
		updateView();
		m_InverseView = glm::inverse(m_View);
		m_InverseProjection = glm::inverse(m_Projection);
		m_InverseViewProjection = m_InverseProjection * m_InverseView;
		m_ViewProjection = m_Projection * m_View;
	}

	void SceneCamera::onImGuiRender()
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("Draw mode"))
		{
			if (ImGui::MenuItem("Lines"))
				Renderer::s_DrawMode = LK_DRAW_LINES;
			else if (ImGui::MenuItem("Triangles"))
				Renderer::s_DrawMode = LK_DRAW_TRIANGLES;
			ImGui::TreePop();
		}
		ImGui::Separator();

		ImGui::SliderFloat("Camera speed", &m_TravelSpeed, 0.010f, 2.0f);
		ImGui::SliderFloat("FOV", &m_FOV, 25.0f, 120.0f);
		ImGui::SliderFloat3("Camera position", &m_Position.x, -40.0f, 40.0f);
	}

}