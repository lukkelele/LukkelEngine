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
		m_View = glm::lookAt(m_Position, m_Position + m_ForwardDir, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void FpsCamera::updateMousePosition()
	{
		std::pair<float, float> mousePos = Mouse::getMousePosition();
		glm::vec2 currentMousePos = glm::vec2(mousePos.first, mousePos.second);
		m_MouseDelta = m_MousePos - currentMousePos;
		m_MousePos = glm::vec2(mousePos.first, mousePos.second);
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
		bool mouseMoved = false;

		glm::vec3 rightDir = glm::cross(m_ForwardDir, m_UpDir);
		// LKLOG_CLIENT_TRACE("POS -> ( {0}, {1}, {2} )", m_Position.x, m_Position.y, m_Position.z);

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
			m_Position -= rightDir * m_Speed * ts;
		} 
		else if (Keyboard::isKeyPressed(Key::D))
		{
			m_Position += rightDir * m_Speed * ts;
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

		updateMousePosition();
		// If the mouse has moved since last frame, update camera rotation
		if (m_MouseDelta.x != 0.0f || m_MouseDelta.y != 0.0f)
		{
			float yaw = m_MouseDelta.x * m_RotationSpeed / 20.0f;
			float pitch = m_MouseDelta.y * m_RotationSpeed / 20.0f;
			glm::quat q = glm::normalize(glm::cross(glm::angleAxis(pitch, rightDir),
				glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f))));

			m_ForwardDir = glm::rotate(q, m_ForwardDir);

			mouseMoved = true;
		}

		if (mouseMoved)
		{
			updateView();
		}

		updateProjection();
		updateView();
		m_ViewProjection = m_Projection * m_View;
	}
}
