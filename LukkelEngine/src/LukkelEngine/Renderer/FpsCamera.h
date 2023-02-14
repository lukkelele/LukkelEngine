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

	class FpsCamera
	{
	public:
		FpsCamera(float FOV, float nearPlane, float farPlane);
		~FpsCamera() = default;

		const glm::vec3& getPosition() const { return m_Position; }
		glm::mat4 getView() const { return m_View; }
		glm::mat4 getProjectionMatrix() const { return m_Projection; }
		glm::mat4 getViewProjectionMatrix() const { return m_ViewProjection; }
		glm::vec3 getForwardDirection() const;
		glm::quat getOrientation() const;
		glm::vec3 calculatePosition() const;

		void setPosition(const glm::vec3& newPos);
		void setProjection(float left, float right, float bottom, float top);
		void setRotation(float rot) { m_Rotation = rot; recalculateView(); }
		void recalculateView();
		void recalculateProjection();

		void onUpdate(float ts);
		void updateView();
		void updateProjection();

		void setPerspective(float FOV, float nearPlane, float farPlane);
		float getPerspectiveFOV() const { return m_FOV; }
		void setPerspectiveFOV(float FOV) { m_FOV = FOV; recalculateProjection(); }
		float getPerspectiveNearClip() const { return m_NearPlane; }
		void setPerspectiveNearClip(float nearClip) { m_NearPlane = nearClip; recalculateProjection(); }
		float getPerspectiveFarClip() const { return m_FarPlane; }
		void setPerspectiveFarClip(float farClip) { m_FarPlane = farClip; recalculateProjection(); }

	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 3.0f };
		glm::vec3 m_Origin = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_MousePos = { 0.0f, 0.0f };
		glm::vec3 m_ForwardDir = { 0.0f, 0.0f, -1.0f };

		float m_FOV = 50.0f, m_NearPlane = 0.10f, m_FarPlane = 1000.0f;
		float m_Distance = 9.0f;
		float m_Speed = 0.010f;

		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.8f;
		float m_Yaw = 0.0f, m_Pitch = 0.0f;
		float m_ViewportWidth = 1280, m_ViewportHeight = 1024;
		float m_AspectRatio = float(16.0f) / float(9.0f);

		glm::mat4 m_View;
		glm::mat4 m_Projection; 
		glm::mat4 m_ViewProjection; 
		glm::mat4 m_InverseView;
		glm::mat4 m_InverseProjection;
	};

}