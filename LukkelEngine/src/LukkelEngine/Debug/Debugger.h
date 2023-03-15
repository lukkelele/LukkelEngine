#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Input/Mouse.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"


namespace LukkelEngine {


	class Debugger
	{
	public:
		Debugger() = default;
		~Debugger() = default;

		template<typename T>
		static void printVec2(T vector, const std::string = "");

		template<typename T>
		static void printVec3(T vector, const std::string = "");
	};

}