#pragma once
#include "LukkelEngine/Core/Base.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Input/Keyboard.h"
#include "LukkelEngine/Input/Mouse.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"

/*
	LukkelEngine: Vector

	As Bullet uses their own btVector's and most of LukkelEngine uses glm::vec,
	this Vector class aims to create one single class to be used for both endpoints
*/

namespace LukkelEngine {

	class Vector3
	{
	public:		
		
		template<typename T, typename Z>
		static Z& convertVec3(T vector);

		static btVector3 btVec3(const glm::vec3& vec);
		static glm::vec3 glmVec3(const btVector3& vec);

	};


	class Vector2
	{
	public:		

	};


}