#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Event/Event.h"

namespace LukkelEngine {

	class Camera
	{
	public:
		Camera(float left, float right, float bottom, float top);
		Camera(float FOV, float nearPlane, float farPlane);
		~Camera() = default;

		const glm::vec3& getPosition() const { return m_Position; }
		glm::mat4 getViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 getProjectionMatrix() const { return m_ProjMatrix; }
		glm::mat4 getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		glm::vec3 getForwardDirection() const;
		glm::quat getOrientation() const;
		glm::vec3 calculatePosition() const;

		void setPosition(const glm::vec3& newPos);
		void setProjection(float left, float right, float bottom, float top);
		// void setRotation(float rot) { m_Rotation = rot; recalculateViewMatrix(); }
		void setRotation(float rot) { m_Rotation = rot; }
		void recalculateViewMatrix();
		void recalculateProjMatrix();

		void onUpdate(float ts);
		void updateView();
		void updateProjection();


		void setPerspective(float FOV, float nearPlane, float farPlane);
		float getPerspectiveFOV() const { return m_PerspectiveFOV; }
		void setPerspectiveFOV(float FOV) { m_PerspectiveFOV = FOV; recalculateProjMatrix(); }
		float getPerspectiveNearClip() const { return m_PerspectiveNear; }
		void setPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; recalculateProjMatrix(); }
		float getPerspectiveFarClip() const { return m_PerspectiveFar; }
		void setPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; recalculateProjMatrix(); }

		float getRotation() { return glm::radians(m_Rotation); }

		void onEvent(Event& e);

	public:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Origin = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Orientation = { 0.0f, 0.0f, -1.0f };
		glm::vec2 m_MousePos = { 0.0f, 0.0f };

		float m_FOV = 50.0f, m_NearPlane = 0.10f, m_FarPlane = 1000.0f;
		float m_Distance = 9.0f;
		float m_Speed = 0.010f;

		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.8f;
		float m_Yaw = 0.0f, m_Pitch = 0.0f;
		float m_ViewportWidth = 1280, m_ViewportHeight = 1024;
		float m_AspectRatio = float(16.0f) / float(9.0f);

		float m_PerspectiveFOV = 50.0f;
		float m_PerspectiveNear = 0.10f;
		float m_PerspectiveFar = 1000.0f;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjMatrix; 
		glm::mat4 m_ViewProjectionMatrix; 
	};

}
