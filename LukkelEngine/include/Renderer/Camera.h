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
		// Stores the main vectors of the camera
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		// Prevents the camera from jumping around when first clicking left click
		bool firstClick = true;

		// Stores the width and height of the window
		int m_Width;
		int m_Height;

		// Adjust the speed of the camera and it's sensitivity when looking around
		float m_Speed = 0.1f;
		float m_Sensitivity = 100.0f;

		// Camera constructor to set up initial values
		Camera(int width, int height, glm::vec3 position);

		// Updates and exports the camera matrix to the Vertex Shader
		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
		// Handles camera inputs
		void Inputs(GLFWwindow* window);
	};

}
