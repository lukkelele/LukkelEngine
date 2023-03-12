#pragma once

// #include "GL/glew.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Input/Mouse.h"


namespace LukkelEngine {

	class Camera {
	public:
		Camera() = default;
		virtual ~Camera() = default;

		// const glm::vec3& getPosition() const { return m_Position; }
	    glm::mat4 getView() const { return m_View; }
	    glm::mat4 getProjection() const { return m_Projection; }
	    glm::mat4 getViewProjection() const { return m_ViewProjection; }

		const float getScreenWidth() const { return m_ViewportWidth; }
		const float getScreenHeight() const { return m_ViewportHeight; }

	protected:
		bool m_MouseEnabled = true;
		bool m_KeyboardEnabled = true;
		float m_MouseSpeed = 1.0f;
		glm::vec2 m_MouseDelta = { 0.0f , 0.0f };


		// TODO: Automate assignment
		float m_ViewportWidth = 1600;
		float m_ViewportHeight = 1024;
		float m_AspectRatio = float(16.0f/9.0f);

		glm::mat4 m_View;
		glm::mat4 m_Projection; 
		glm::mat4 m_ViewProjection; 
		glm::mat4 m_InverseView;
		glm::mat4 m_InverseProjection;
		glm::mat4 m_InverseViewProjection;
	};

}
