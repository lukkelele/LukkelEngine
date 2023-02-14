#include "LukkelEngine/Renderer/FpsCamera.h"


namespace LukkelEngine {

	FpsCamera::FpsCamera(float FOV, float nearPlane, float farPlane)
		: m_FOV(FOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
	}

	void FpsCamera::recalculateProjection()
	{
		m_Projection = glm::perspectiveFov(glm::radians(m_FOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearPlane, m_FarPlane);
		m_InverseProjection = glm::inverse(m_Projection);
	}

	void FpsCamera::recalculateView()
	{
		m_View = glm::lookAt(m_Position, m_Position + m_ForwardDir, glm::vec3(0, 1, 0));
		m_InverseView = glm::inverse(m_View);
	}

	void FpsCamera::onUpdate(float ts)
	{
		// glm::vec2 deltaTime = (mousePos - m_LastMousePos) * 0.002f;

		glm::vec3 upDir = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 rightDir = glm::cross(m_ForwardDir, upDir);

		float camSpeed = 2.0f;

		if (Keyboard::isKeyPressed(Key::W))
		{
			LKLOG_INFO("W");
			m_Position += m_ForwardDir * camSpeed * ts;
		} 
		else if (Keyboard::isKeyPressed(Key::S))
		{
			LKLOG_INFO("S");
			m_Position -= m_ForwardDir * camSpeed * ts;
		} 
		if (Keyboard::isKeyPressed(Key::A)) 
		{
			LKLOG_INFO("A");
			m_Position += rightDir * camSpeed * ts;
		} 
		else if (Keyboard::isKeyPressed(Key::D))
		{
			LKLOG_INFO("D");
			m_Position -= rightDir * camSpeed * ts;
		}

		// ROTATION
		if (Keyboard::isKeyPressed(Key::Q))
		{
			m_Rotation += m_RotationSpeed * ts;
			setRotation(m_Rotation);
			LKLOG_WARN("Yaw: {0} | Pitch: {1}", m_Yaw, m_Pitch);
		}
		else if (Keyboard::isKeyPressed(Key::E))
		{
			m_Rotation -= m_RotationSpeed * ts;
			setRotation(m_Rotation);
			LKLOG_WARN("Yaw: {0} | Pitch: {1}", m_Yaw, m_Pitch);
		}

		if (Keyboard::isKeyPressed(Key::R))
		{
			m_Position.z += m_Speed * ts;
		}
		else if (Keyboard::isKeyPressed(Key::T))
		{
			m_Position.z -= m_Speed * ts;
		}
	}
}