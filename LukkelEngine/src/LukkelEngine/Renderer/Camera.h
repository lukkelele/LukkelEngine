#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "LukkelEngine/Renderer/Shader.h"

namespace LukkelEngine {

	class Camera
	{
	public:
		Camera(float left, float right, float bottom, float top);
		~Camera() = default;

		const glm::vec3& getPosition() const { return m_Position; }
		glm::mat4 getViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 getProjectionMatrix() const { return m_ProjectionMatrix; }
		glm::mat4 getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		glm::vec3 getForwardDirection() const;
		glm::quat getOrientation() const;
		glm::vec3 calculatePosition() const;

		void setPosition(const glm::vec3& newPos);
		// Could recalculate view matrix in 'onUpdate' as well
		void setProjection(float left, float right, float bottom, float top);
		void setRotation(float rot) { m_Rotation = rot; recalculateViewMatrix(); }
		void recalculateViewMatrix();

		void updateView();
		void updateProjection();

	// TODO: SET ME TO PRIVATE
	public:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Origin = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_MousePos = { 0.0f, 0.0f };

		float m_FOV = 50.0f, m_NearPlane = 0.10f, m_FarPlane = 1000.0f;
		float m_Distance = 9.0f;

		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.10f;
		float m_Yaw = 0.0f, m_Pitch = 0.0f;
		float m_ViewportWidth = 1280, m_ViewportHeight = 1024;
		float m_AspectRatio = 1.5f;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix; 
		glm::mat4 m_ViewProjectionMatrix; 
	};

}
