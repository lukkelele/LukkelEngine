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
}