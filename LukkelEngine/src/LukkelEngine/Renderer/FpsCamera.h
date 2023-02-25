#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Input/Mouse.h"


namespace LukkelEngine {

	class FpsCamera	{
	public:
		FpsCamera(float FOV, float nearPlane, float farPlane);
		~FpsCamera() = default;

		void onUpdate(float ts);

		glm::mat4 getView() const { return m_View; }
		glm::mat4 getProjection() const { return m_Projection; }
		glm::mat4 getViewProjection() { return m_ViewProjection; }
		glm::vec3 calculatePosition() const;

		glm::quat getOrientation() const;
		glm::vec3 getRightDirection() const;
		glm::vec3 getForwardDirection() const;
		glm::vec3 getUpDirection() const;

		const glm::vec3& getPosition() const { return m_Position; }
		float getFOV() const { return m_FOV; }
		float getNearClip() const { return m_NearPlane; }
		float getFarClip() const { return m_FarPlane; }
		float getRotation() { return glm::radians(m_Rotation); }

		void setPosition(glm::vec3& pos) { m_Position = pos; }
		void setRotation(float rot) { m_Rotation = rot; }
		void setFOV(float FOV) { m_FOV = FOV; updateProjection(); }
		void setNearClip(float nearClip) { m_NearPlane = nearClip; }
		void setFarClip(float farClip) { m_FarPlane = farClip; }
        void setTarget(glm::vec3 target) { m_Target = target; }

		void updateView();
		void updateProjection();
		void updateMousePosition();

		// void onMouseScroll(MouseScrolledEvent& e);

	public:
		glm::vec3 m_Position = { 0.0f, 0.0f, -6.0f };
		glm::vec3 m_Direction = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Origin = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_MousePos = { 0.0f, 0.0f };

		glm::vec3 m_ForwardDir = { 0.0f, 0.0f, 1.0f };
		glm::vec3 m_UpDir = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::vec3 m_Target = { 0.0f, 0.0f, 0.0f };

		float m_FOV = 50.0f, m_NearPlane = 0.10f, m_FarPlane = 1000.0f;
		float m_Speed = 0.05f;
		float m_Distance = 0.5f;

		bool m_MouseEnabled = true;
		bool m_KeyboardEnabled = true;

		float m_MouseSpeed = 1.0f;
		glm::vec2 m_MouseDelta = { 0.0f , 0.0f };

		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.0002f;
		float m_Yaw = 0.0f, m_Pitch = 0.0f;
		float m_ViewportWidth = 1600, m_ViewportHeight = 1024;
		float m_AspectRatio = float(16.0f/9.0f);

		glm::mat4 m_View;
		glm::mat4 m_Projection; 
		glm::mat4 m_ViewProjection; 
		glm::mat4 m_InverseView;
		glm::mat4 m_InverseProjection;
	};

}
