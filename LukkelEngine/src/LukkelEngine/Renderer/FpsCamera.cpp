#include "LKpch.h"
#include "LukkelEngine/Renderer/FpsCamera.h"
#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	FpsCamera::FpsCamera(float FOV, float nearPlane, float farPlane)
		: m_FOV(FOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		LKLOG_TRACE("FPS Camera created | FOV: {0}", m_FOV);
		m_View = glm::mat4(1.0f);
		m_Projection = glm::perspectiveFov(glm::radians(m_FOV), m_ViewportWidth, m_ViewportHeight, m_NearPlane, m_FarPlane);
		m_ViewProjection = m_Projection * m_View;
	}

	void FpsCamera::updateProjection()
	{
		m_Projection = glm::perspectiveFov(glm::radians(m_FOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearPlane, m_FarPlane);
	}

	void FpsCamera::updateView()
	{
		m_View = glm::lookAt(m_Position, m_Position + m_ForwardDir, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void FpsCamera::updateMousePosition()
	{
		std::pair<float, float> mousePos = Mouse::getMousePosition();
		glm::vec2 currentMousePos = glm::vec2(mousePos.first, mousePos.second);
		m_MouseDelta = m_MousePos - currentMousePos;
		m_MousePos = glm::vec2(mousePos.first, mousePos.second);
		if (Keyboard::isKeyPressed(Key::Escape))
			m_MouseEnabled = false;
	}

	glm::vec3 FpsCamera::getUpDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 FpsCamera::getRightDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 FpsCamera::getForwardDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat FpsCamera::getOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

	glm::vec3 FpsCamera::getDirection() const
	{
		return m_Direction;
	}

	void FpsCamera::updateDirection()
	{
		// If not in radians
		// m_Direction.x = cos(glm::radians(m_Yaw));
		// m_Direction.y = sin(glm::radians(m_Pitch));
		// m_Direction.z = sin(glm::radians(m_Yaw));
		m_Direction.x = cos(m_Yaw);
		m_Direction.y = sin(m_Pitch);
		m_Direction.z = sin(m_Yaw);
	}

	glm::vec3 FpsCamera::calculatePosition() const
	{
		return m_Origin - getForwardDirection() * m_Distance;
	}


	void FpsCamera::onUpdate(float ts)
	{
		glm::vec3 rightDir = glm::cross(m_ForwardDir, m_UpDir); 

		if (m_KeyboardEnabled)
		{
			// WASD
			if (Keyboard::isKeyPressed(Key::W))
				m_Position += m_ForwardDir * m_TravelSpeed * ts;
			else if (Keyboard::isKeyPressed(Key::S))
				m_Position -= m_ForwardDir * m_TravelSpeed * ts;
			if (Keyboard::isKeyPressed(Key::A)) 
				m_Position -= rightDir * m_TravelSpeed * ts;
			else if (Keyboard::isKeyPressed(Key::D))
				m_Position += rightDir * m_TravelSpeed * ts;
		}

		if (Mouse::isButtonPressed(MouseButton::Button0))
		{
			RaycastResult r;
			btVector3 pos = Vector3::btVec3(m_Position);
			btVector3 target = Vector3::btVec3(m_ForwardDir);
			bool hitReg = m_Scene->m_World->raycast(r, pos, target);
			if (hitReg)
				LKLOG_CRITICAL("HITREG: 1");
			else
				LKLOG_INFO("HITREG: 0");
		}


		// Release mouse focus
		if (Keyboard::isKeyPressed(Key::Escape))
		{
			if (m_MouseEnabled)
			{
				Application::get().getWindow()->setInputLock(false);
				m_MouseEnabled = false;
			}
		}
		// Reinstate mouse focus
		else if (Keyboard::isKeyPressed(Key::G))
		{
			if (!m_MouseEnabled)
			{
				Application::get().getWindow()->setInputLock(true);
				m_MouseEnabled = true;
			}
		}

		updateMousePosition();
		// If the mouse has moved since last frame, update camera rotation
		if (m_MouseEnabled)
		{
			if (m_MouseDelta.x != 0.0f || m_MouseDelta.y != 0.0f)
			{
				float yaw = m_MouseDelta.x * m_RotationSpeed;
				float pitch = m_MouseDelta.y * m_RotationSpeed;
				m_Yaw = yaw; m_Pitch = pitch;

				glm::quat quat = glm::normalize(glm::cross(glm::angleAxis(pitch, rightDir),
					glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f))));

				m_ForwardDir = glm::rotate(quat, m_ForwardDir);
			}

		}
		updateProjection();
		updateView();
		m_ViewProjection = m_Projection * m_View;
	}

	void FpsCamera::onImGuiRender()
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
