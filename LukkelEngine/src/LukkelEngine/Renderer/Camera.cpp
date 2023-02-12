#include "LukkelEngine/Renderer/Camera.h"

namespace LukkelEngine {

	Camera::Camera(float FOV, float nearPlane, float farPlane)
		: m_FOV(FOV), m_NearPlane(nearPlane),
		  m_FarPlane(farPlane)
	{
		m_ViewMat = glm::lookAt(m_Position, m_Front, m_Up);
		m_ProjMat = glm::perspective(FOV, (m_ViewportWidth / m_ViewportHeight), nearPlane, farPlane);
		LKLOG_TRACE("Camera created | FOV: {0}", FOV);
	}

	// Change to 3 floats instead ?
	void Camera::setPosition(glm::vec3 newPos) {
		m_Position = newPos; // set (x, y, z) to new pos
		LKLOG_TRACE("Position: ({0}, {1}, {2})", m_Position.x, m_Position.y, m_Position.z);
		recalculateViewMatrix();
	}

	void Camera::setVecPosition(VecPos p, float value)
	{
		switch (p)
		{
			case (VecPos::x): {
				m_Position.x = value;
				break;
			} 
			case (VecPos::y): {
				m_Position.y = value;
				break;
			}
			case (VecPos::z): {
				m_Position.z = value;
				break;
			}
		}
	}

	void Camera::recalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		m_ViewMat = glm::inverse(transform);
		m_MVP = m_ProjMat * m_ViewMat;
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
}