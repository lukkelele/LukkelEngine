#include "LukkelEngine/Renderer/Camera.h"

namespace LukkelEngine {

	Camera::Camera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		LKLOG_TRACE("Camera created | FOV: {0}", m_FOV);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	// Change to 3 floats instead ?
	void Camera::setPosition(const glm::vec3 &newPos) {
		m_Position = newPos; 
		LKLOG_CLIENT_WARN("Camera position: ({0}, {1}, {2})", m_Position.x, m_Position.y, m_Position.z);
		recalculateViewMatrix();
	}

	void Camera::setProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
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
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
	}

	void Camera::recalculateViewMatrix()
	{
		LKLOG_CLIENT_TRACE("recalculateViewMatrix() -> cam position: ({0}, {1}, {2})", m_Position.x, m_Position.y, m_Position.z);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
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