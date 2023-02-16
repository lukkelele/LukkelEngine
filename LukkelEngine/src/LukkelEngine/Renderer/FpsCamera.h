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
		float getFOV() const { return m_FOV; }
		float getNearClip() const { return m_NearPlane; }
		float getFarClip() const { return m_FarPlane; }
		float getRotation() { return glm::radians(m_Rotation); }

		void setPosition(const glm::vec3& newPos);
		void setProjection(float left, float right, float bottom, float top);
		void setRotation(float rot) { m_Rotation = rot; recalculateView(); }
		void setFOV(float FOV) { m_FOV = FOV; recalculateProjection(); }
		void setNearClip(float nearClip) { m_NearPlane = nearClip; recalculateProjection(); }
		void setFarClip(float farClip) { m_FarPlane = farClip; recalculateProjection(); }
        void setTarget(glm::vec3 target) { m_Target = target; }

		void recalculateView();
		void recalculateProjection();

		void onUpdate(float ts);
		void updateView();
		void updateProjection();

	public:
		glm::vec3 m_Position = { 0.0f, 0.0f, -200.0f };
		glm::vec3 m_Origin = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_MousePos = { 0.0f, 0.0f };

		glm::vec3 m_ForwardDir = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_Target = { 0.0f, 0.0f, 0.0f };

		float m_FOV = 50.0f, m_NearPlane = 0.10f, m_FarPlane = 1000.0f;
		float m_Speed = 0.45f;

		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.2f;
		float m_Yaw = 0.0f, m_Pitch = 0.0f;
		float m_ViewportWidth = 1280, m_ViewportHeight = 1024;
		float m_AspectRatio = float(16.0f/9.0f);

		glm::mat4 m_View;
		glm::mat4 m_Projection; 
		glm::mat4 m_ViewProjection; 
		glm::mat4 m_InverseView;
		glm::mat4 m_InverseProjection;
	};

}
