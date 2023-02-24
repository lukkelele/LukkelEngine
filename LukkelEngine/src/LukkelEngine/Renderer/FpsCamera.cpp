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

	glm::vec3 FpsCamera::calculatePosition() const
	{
		return m_Origin - getForwardDirection() * m_Distance;
	}


	void FpsCamera::onUpdate(float ts)
	{
		// FIXME: Gets calculated even though both mouse and keyboard can be disconnected
		glm::vec3 rightDir = glm::cross(m_ForwardDir, m_UpDir); 

		if (m_KeyboardEnabled)
		{
			// WASD
			if (Keyboard::isKeyPressed(Key::W))
				m_Position += m_ForwardDir * m_Speed * ts;
			else if (Keyboard::isKeyPressed(Key::S))
				m_Position -= m_ForwardDir * m_Speed * ts;
			if (Keyboard::isKeyPressed(Key::A)) 
				m_Position -= rightDir * m_Speed * ts;
			else if (Keyboard::isKeyPressed(Key::D))
				m_Position += rightDir * m_Speed * ts;

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
		if (Keyboard::isKeyPressed(Key::G))
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
				glm::quat quat = glm::normalize(glm::cross(glm::angleAxis(pitch, rightDir),
					glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f))));

				m_ForwardDir = glm::rotate(quat, m_ForwardDir);
			}
		}

		updateProjection();
		updateView();
		m_ViewProjection = m_Projection * m_View;
	}
}
