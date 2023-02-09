#include <Camera.h>

namespace LukkelEngine {

	Camera::Camera(float FOV, float width, float height, float nearPlane,
				   float farPlane, glm::vec3 camPos)
		: m_FOV(FOV), m_Width(width), m_Height(height), m_NearPlane(nearPlane),
		  m_FarPlane(farPlane), m_Pos(camPos)
	{
		/* Perform matrix operations */
		m_ViewMat = glm::lookAt(m_Pos, m_Front, m_Up);
		m_ProjMat = glm::perspective(FOV, (width / height), nearPlane, farPlane);
	}

	Camera::~Camera(){}

	void Camera::setPosition(glm::vec3 newPos) {
		m_Pos = newPos; // set (x, y, z) to new pos
		recalculateViewMatrix();
	}

	void Camera::recalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Pos) *
			glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		m_ViewMat = glm::inverse(transform);
		m_MVP = m_ProjMat * m_ViewMat;
	}
}