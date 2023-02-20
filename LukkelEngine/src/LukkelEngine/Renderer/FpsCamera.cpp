#include "LukkelEngine/Renderer/FpsCamera.h"


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
		m_Position = calculatePosition();

		glm::quat orientation = getOrientation();
		m_View= glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_View = glm::inverse(m_View);
	}

	void FpsCamera::updateMousePosition()
	{
		std::pair<float, float> mousePos = Mouse::getMousePosition();
		m_MousePos.x = mousePos.first;
		m_MousePos.y = mousePos.second;
	}

	void FpsCamera::mouseRotate(glm::vec2& delta)
	{
		float yawSign = getUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * m_RotationSpeed;
		m_Pitch += delta.y * m_RotationSpeed;
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

	glm::vec3 FpsCamera::calculatePosition() const
	{
		return m_Origin - getForwardDirection() * m_Distance;
	}


	void FpsCamera::onUpdate(float ts)
	{
		// LKLOG_CLIENT_TRACE("POS -> ( {0}, {1}, {2} )", m_Position.x, m_Position.y, m_Position.z);
		updateMousePosition();
		// TODO: Fix mouse rotation
		// mouseRotate(glm::vec2(m_MousePos.x, m_MousePos.y));
		horizontalAngle += m_MouseSpeed * ts * float(m_ViewportWidth / 2 - m_MousePos.x);
		verticalAngle += m_MouseSpeed * ts * float(m_ViewportHeight / 2 - m_MousePos.y);

		// Right vector

		if (Keyboard::isKeyPressed(Key::W))
		{
			m_Position += m_ForwardDir * m_Speed * ts;
		} 
		else if (Keyboard::isKeyPressed(Key::S))
		{
			m_Position -= m_ForwardDir * m_Speed * ts;
		} 
		if (Keyboard::isKeyPressed(Key::A)) 
		{
			// m_Position.x += m_Speed * ts;
			m_Position += getRightDirection() * m_Speed * ts;
		} 
		else if (Keyboard::isKeyPressed(Key::D))
		{
			m_Position -= getRightDirection() * m_Speed * ts;
		}

		// ROTATION
		if (Keyboard::isKeyPressed(Key::Q))
		{
			m_Rotation += m_RotationSpeed * ts;
			setRotation(m_Rotation);
		}
		else if (Keyboard::isKeyPressed(Key::E))
		{
			m_Rotation -= m_RotationSpeed * ts;
			setRotation(m_Rotation);
		}

		// ARROW KEYS
		if (Keyboard::isKeyPressed(Key::Up))
		{
			// m_Position.y -= m_Speed * ts;
			m_FOV += 1;
		}
		else if (Keyboard::isKeyPressed(Key::Down))
		{
			// m_Position.y += m_Speed * ts;
			m_FOV -= 1;
		}

		updateProjection();
		m_ViewProjection = m_Projection * m_View;
	}
}
