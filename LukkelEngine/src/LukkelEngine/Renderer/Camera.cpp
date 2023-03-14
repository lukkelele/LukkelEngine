#include "LKpch.h"
#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Scene/Scene.h"

#include <imgui/imgui.h>


namespace LukkelEngine {

	Camera::Camera(float FOV, float nearPlane, float farPlane)
		: m_FOV(FOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		LKLOG_INFO("FPS Camera created | FOV: {0}", m_FOV);
		const glm::quat orientation = getOrientation();

		m_Yaw = 3.0f * glm::pi<float>() / 4.0f;
		m_Pitch = glm::pi<float>() / 4.0f;

		m_Projection = glm::perspectiveFov(glm::radians(m_FOV), m_ViewportWidth, m_ViewportHeight, m_NearPlane, m_FarPlane);
		m_View = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewProjection = m_Projection * m_View;
	}

	glm::quat Camera::getOrientation() const
	{
		return glm::quat(glm::vec3(m_Pitch, m_Yaw, 0.0f));
	}

	void Camera::updateProjection()
	{
		m_Projection = glm::perspectiveFov(glm::radians(m_FOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearPlane, m_FarPlane);
	}

	void Camera::updateView()
	{
		m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera::updateMousePosition()
	{
		const glm::vec2& mousePos { Mouse::getMouseX(), Mouse::getMouseY() };
		m_MouseDelta = (mousePos - m_MousePos);
		m_MousePos = mousePos;

		if (Keyboard::isKeyPressed(Key::Escape))
			m_MouseEnabled = false;
	}

	glm::vec3 Camera::getUpDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 Camera::getRightDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 Camera::getForwardDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 Camera::getDirection()
	{
		glm::vec3 lookAt = m_Position + getForwardDirection();
		m_Direction = glm::normalize(lookAt - m_Position);
		return m_Direction;
	}

	glm::vec3 Camera::calculatePosition() const
	{
		return m_Origin - getForwardDirection() * m_Distance;
	}

	// Basic Camera settings
	void Camera::onImGuiRender()
	{
	 	ImGui::Begin("Camera settings");

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

		// Sliders
	 	ImGui::SliderFloat("Camera speed", &m_TravelSpeed, 0.010f, 2.0f);
		float fov = getFOV();
	 	ImGui::SliderFloat("FOV", &fov, 40.0f, 105.0f);
		setFOV(fov);
		glm::vec3 pos = getPosition();
	 	ImGui::SliderFloat3("Camera position", &pos.x, -50.0f, 50.0f);
		setPosition(pos);

		ImGui::End();
	}

}