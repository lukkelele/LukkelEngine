#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <Shader.h>

namespace LukkelEngine {

	class Camera
	{
	public:
		Camera(float FOV = 90.0f, float width = 800, float height = 600, float nearPlane = 0.10f,
			   float farPlane = 100.0f, glm::vec3 camPos = glm::vec3(0.0f, 4.0f, 6.0f));
		~Camera();

		glm::vec3 getCameraPosition() { return m_Pos; }
		glm::mat4 getViewMatrix() { return m_ViewMat; }
		glm::mat4 getProjectionMatrix() { return m_ProjMat; }

		void setPosition(glm::vec3 newPos);
		// Could recalculate view matrix in 'onUpdate' as well
		void setRotation(float rot) { m_Rotation = rot; recalculateViewMatrix(); }
		void recalculateViewMatrix();

	private:
		glm::vec3 m_Pos;
		float m_Width, m_Height;
		float m_FOV, m_NearPlane, m_FarPlane;
		float m_Rotation = 0.0f;
		float m_RotationSpeed = 0.10f;
		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 m_ViewMat;
		glm::mat4 m_ProjMat;
		glm::mat4 m_MVP; // view projection matrix
	};

}
