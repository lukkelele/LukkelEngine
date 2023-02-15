#include "LukkelEngine/Renderer/Camera.h"

namespace LukkelEngine {

	Camera::Camera(float left, float right, float bottom, float top)
		: m_ProjMatrix(glm::ortho(left, right, bottom, top, -10.0f, 100.0f)), m_ViewMatrix(1.0f)
	{
		LKLOG_TRACE("Camera created | FOV: {0}", m_FOV);
		m_ViewProjectionMatrix = m_ProjMatrix * m_ViewMatrix;
	}

	Camera::Camera(float FOV, float nearPlane, float farPlane)
		: m_FOV(FOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
	}

	// Change to 3 floats instead ?
	void Camera::setPosition(const glm::vec3 &newPos) {
		m_Position = newPos; 
		LKLOG_CLIENT_WARN("Camera position: ({0}, {1}, {2})", m_Position.x, m_Position.y, m_Position.z);
		recalculateViewMatrix();
	}

	void Camera::setProjection(float left, float right, float bottom, float top)
	{
		m_ProjMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjMatrix * m_ViewMatrix;
	}

	void Camera::updateView()
	{
		m_Position = calculatePosition();
		glm::quat orientation = getOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	void Camera::updateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_ProjMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
	}

	void Camera::recalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjMatrix * m_ViewMatrix;
	}

	void Camera::recalculateProjMatrix()
	{
		m_ProjMatrix = glm::perspective(m_PerspectiveFOV, (float)m_ViewportWidth/m_ViewportHeight, m_PerspectiveNear, m_PerspectiveFar);
	}

	void Camera::setPerspective(float FOV, float nearPlane, float farPlane)
	{
		m_PerspectiveFOV = FOV;
		m_PerspectiveNear = nearPlane;
		m_PerspectiveFar = farPlane;
		recalculateProjMatrix();
	}

	glm::vec3 Camera::getForwardDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat Camera::getOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

	glm::vec3 Camera::calculatePosition() const
	{
		return (m_Origin - getForwardDirection() * m_Distance);
	}

	void Camera::onUpdate(float ts)
	{
		if (Keyboard::isKeyPressed(Key::W))
		{
			LKLOG_INFO("W");
			// m_Position.y -= m_Speed * ts;
			glm::vec3 forward(0, 0, 1);
			m_Position += forward * 0.1f;
			LKLOG_CLIENT_TRACE("POS -> ( {0}, {1}, {2} )", m_Position.x, m_Position.y, m_Position.y);
		} 
		else if (Keyboard::isKeyPressed(Key::S))
		{
			LKLOG_INFO("S");
			// m_Position.y -= m_Speed * ts;
			glm::vec3 forward(0, 0, 1);
			m_Position -= forward * 0.1f;
			LKLOG_CLIENT_TRACE("POS -> ( {0}, {1}, {2} )", m_Position.x, m_Position.y, m_Position.y);
		} 
		if (Keyboard::isKeyPressed(Key::A)) 
		{
			LKLOG_INFO("A");
			m_Position.x += m_Speed * ts;
		} 
		else if (Keyboard::isKeyPressed(Key::D))
		{
			LKLOG_INFO("D");
			m_Position.x -= m_Speed * ts;
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

		// ARROW KEYS
		if (Keyboard::isKeyPressed(Key::Up))
		{
			m_Position.y -= m_Speed * ts;
		}
		else if (Keyboard::isKeyPressed(Key::Down))
		{
			m_Position.y += m_Speed * ts;
		}

		// recalculateProjMatrix();
		recalculateViewMatrix();
	}

}