#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


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

		void onUpdate(float ts) override;
		void onImGuiRender() override;

	public:
		float m_TravelSpeed = 0.10f;
		float m_Distance = 500.0f;
	};

}
