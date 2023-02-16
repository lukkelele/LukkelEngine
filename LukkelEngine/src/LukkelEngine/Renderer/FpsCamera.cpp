#include "LukkelEngine/Renderer/FpsCamera.h"


/**
 * TODO: Clipping and warping  40.0 < FOV < 90
*/

namespace LukkelEngine {

	FpsCamera::FpsCamera(float FOV, float nearPlane, float farPlane)
		: m_FOV(FOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		LKLOG_TRACE("FPS Camera created | FOV: {0}", m_FOV);
		m_View = glm::mat4(1.0f);
		m_Projection = glm::perspectiveFov(m_FOV, m_ViewportWidth, m_ViewportHeight, m_NearPlane, m_FarPlane);
		m_ViewProjection = m_Projection * m_View;
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
		if (Keyboard::isKeyPressed(Key::W))
		{
			LKLOG_INFO("W");
			m_Position.z += m_Speed * ts;
			LKLOG_CLIENT_TRACE("POS -> ( {0}, {1}, {2} )", m_Position.x, m_Position.y, m_Position.z);
		} 
		else if (Keyboard::isKeyPressed(Key::S))
		{
			LKLOG_INFO("S");
			m_Position.z -= m_Speed * ts;
			LKLOG_CLIENT_TRACE("POS -> ( {0}, {1}, {2} )", m_Position.x, m_Position.y, m_Position.z);
		} 
		if (Keyboard::isKeyPressed(Key::A)) 
		{
			LKLOG_INFO("A");
			m_Position.x -= m_Speed * ts;
		} 
		else if (Keyboard::isKeyPressed(Key::D))
		{
			LKLOG_INFO("D");
			m_Position.x += m_Speed * ts;
		}

		// ROTATION
		if (Keyboard::isKeyPressed(Key::Q))
		{
			m_Rotation += m_RotationSpeed * ts;
			LKLOG_TRACE("Rotation speed: {0}", m_RotationSpeed);
			setRotation(m_Rotation);
			LKLOG_WARN("Yaw: {0} | Pitch: {1}", m_Yaw, m_Pitch);
		}
		else if (Keyboard::isKeyPressed(Key::E))
		{
			m_Rotation -= m_RotationSpeed * ts;
			setRotation(m_Rotation);
			LKLOG_WARN("Yaw: {0} | Pitch: {1}", m_Yaw, m_Pitch);
		}

		// ARROW KEYS
		if (Keyboard::isKeyPressed(Key::Up))
		{
			m_Position.y -= m_Speed * ts;
		}
		else if (Keyboard::isKeyPressed(Key::Down))
		{
			m_Position.y += m_Speed * ts;
		}

		//recalculateProjection();
		recalculateView();
	}
}
