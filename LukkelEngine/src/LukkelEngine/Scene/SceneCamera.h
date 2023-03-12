#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtc/quaternion.hpp"

#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Input/Mouse.h"

namespace LukkelEngine {

	class Scene;

	class SceneCamera : public Camera
	{
	public:
		SceneCamera(float FOV, float nearPlane, float farPlane);
		~SceneCamera() = default;

		void onUpdate(float ts);
		void onImGuiRender();

		glm::vec3 calculatePosition() const;
		glm::quat getOrientation() const;
		glm::vec3 getDirection();
		glm::vec3 getRightDirection() const;
		glm::vec3 getForwardDirection() const;
		glm::vec3 getUpDirection() const;
		glm::mat4& getInverseViewProjection() { return m_InverseViewProjection; }
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
		void setScene(Scene* scene) { m_Scene = scene; }

		void updateView();
		void updateProjection();
		void updateMousePosition();
		// void onMouseScroll(MouseScrolledEvent& e);
		bool hasMouseMoved;

	public:
		glm::vec3 m_Position = { 0.0f, 0.0f, -10.0f };
		glm::vec3 m_Direction;
		glm::vec3 m_Origin = { 0.0f, 0.0f, 0.0f };

		glm::vec3 m_ForwardDirection = { 0.0f, 0.0f, 1.0f };
		glm::vec3 m_UpDirection = { 0.0f, 1.0f, 0.0f };
		glm::vec3 m_RightDirection{};
		glm::vec3 m_PositionDelta{};

		float m_FOV = 50.0f, m_NearPlane = 0.10f, m_FarPlane = 1000.0f;
		float m_TravelSpeed = 0.10f;
		float m_Distance = 500.0f;

		bool m_KeyboardEnabled = true;
		bool m_MouseEnabled = true;

		float m_MouseSpeed = 1.0f;
		glm::vec2 m_MousePos = { 0.0f, 0.0f };
		glm::vec2 m_InitialMousePos{};
		glm::vec2 m_MouseDelta = { 0.0f , 0.0f };

		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.0002f;
		float m_Yaw = 0.0f, m_Pitch = 0.0f;
		float m_YawDelta = 0.0f, m_PitchDelta = 0.0f;

		friend class Scene;
		Scene* m_Scene;
	};

}
