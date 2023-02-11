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

	/* Vector position -> (x, y, z) */
	enum VecPos {
		x = 0,
		y = 1,
		z = 2
	};

	class Camera
	{
	public:
		Camera(float FOV = 50.0f, float nearPlane = 0.10f, float farPlane = 100.0f);
		~Camera() = default;


		glm::vec3 getPosition() const { return m_Position; }
		glm::mat4 getViewMatrix() const { return m_ViewMat; }
		glm::mat4 getProjectionMatrix() const { return m_ProjMat; }
		glm::vec3 getForwardDirection() const;
		glm::quat getOrientation() const;
		glm::vec3 calculatePosition() const;

		void setPosition(glm::vec3 newPos);
		// Could recalculate view matrix in 'onUpdate' as well
		void setRotation(float rot) { m_Rotation = rot; recalculateViewMatrix(); }
		void recalculateViewMatrix();

		void setVecPosition(VecPos p, float value);
		// void bindKeyboard(Keyboard* keyboard);

	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Origin = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_MousePos = { 0.0f, 0.0f };


		float m_FOV = 50.0f, m_NearPlane = 0.10f, m_FarPlane = 1000.0f;
		float m_Distance = 9.0f;

		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.10f;
		float m_Yaw, m_Pitch = 0.0f;

		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 m_ViewMat;
		glm::mat4 m_ProjMat;
		glm::mat4 m_MVP; // view projection matrix

		float m_ViewportWidth = 1280, m_ViewportHeight = 1024;
	};

}
