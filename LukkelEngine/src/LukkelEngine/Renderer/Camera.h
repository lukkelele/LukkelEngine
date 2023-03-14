#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Input/Mouse.h"


namespace LukkelEngine {

	class Scene; // Forward Declaration

	class Camera {
	public:
		Camera() = default;
		Camera(float FOV, float nearPlane, float farPlane);
		virtual ~Camera() = default;

		virtual void onUpdate(float ts) {}
		virtual void onImGuiRender();

		const glm::vec3& getPosition() const { return m_Position; }
	    glm::mat4 getView() const { return m_View; }
	    glm::mat4 getProjection() const { return m_Projection; }
	    glm::mat4 getViewProjection() const { return m_ViewProjection; }
		glm::quat getOrientation() const;
		glm::vec3 getDirection();
		glm::vec3 calculatePosition() const;
		glm::mat4& getInverseViewProjection() { return m_InverseViewProjection; }
		glm::vec3 getRightDirection() const;
		glm::vec3 getForwardDirection() const;
		glm::vec3 getUpDirection() const;

		const float getScreenWidth() const { return m_ViewportWidth; }
		const float getScreenHeight() const { return m_ViewportHeight; }

		float getFOV() const { return m_FOV; }
		float getNearClip() const { return m_NearPlane; }
		float getFarClip() const { return m_FarPlane; }
		float getRotation() { return glm::radians(m_Rotation); }

		void setPosition(glm::vec3& pos) { m_Position = pos; }
		void setRotation(float rot) { m_Rotation = rot; }
		void setFOV(float FOV) { m_FOV = FOV; updateProjection(); }
		void setNearClip(float nearClip) { m_NearPlane = nearClip; }
		void setFarClip(float farClip) { m_FarPlane = farClip; }
		void setScene(Scene* scene) { m_Scene = scene; }

		void updateView();
		void updateProjection();
		void updateMousePosition();

		bool hasMouseMoved;

	protected:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_PositionDelta{};
		glm::vec3 m_Origin = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_MouseDelta = { 0.0f , 0.0f };

		glm::vec3 m_Direction{};
		glm::vec3 m_ForwardDirection = { 0.0f, 0.0f, 1.0f };
		glm::vec3 m_UpDirection = { 0.0f, 1.0f, 0.0f };
		glm::vec3 m_RightDirection{};

		float m_FOV = 50.0f;
		float m_NearPlane = 0.10f, m_FarPlane = 1000.0f;
		float m_TravelSpeed = 0.10f;
		float m_Distance = 500.0f;

		bool m_KeyboardEnabled = true;
		bool m_MouseEnabled = true;

		float m_MouseSpeed = 1.0f;
		glm::vec2 m_MousePos = { 0.0f, 0.0f };
		glm::vec2 m_InitialMousePos{};

		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.0002f;
		float m_Yaw = 0.0f, m_Pitch = 0.0f;
		float m_YawDelta = 0.0f, m_PitchDelta = 0.0f;

		glm::mat4 m_View;
		glm::mat4 m_Projection; 
		glm::mat4 m_ViewProjection; 
		glm::mat4 m_InverseView;
		glm::mat4 m_InverseProjection;
		glm::mat4 m_InverseViewProjection;

		// ----------------- TO BE FIXED ---------------------
		// TODO: Automate assignment
		float m_ViewportWidth = 2200;
		float m_ViewportHeight = 1240;
		float m_AspectRatio = float(16.0f/9.0f);

		friend class Scene;
		Scene* m_Scene;
	};

}
