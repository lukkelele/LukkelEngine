#pragma once

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Debug/Debugger.h"
#include "LukkelEngine/Physics/Rigidbody.h"
#include "LukkelEngine/Physics/MotionState.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	class RigidbodyFactory
	{
	public:
		RigidbodyFactory();
		~RigidbodyFactory() = default;

		static Rigidbody CreateRigidbody(UUID id, Rigidbody::Shape shape, Rigidbody::Type bodyType, 
										 glm::vec3 dimensions, glm::vec3 offset, float mass, 
										 float friction = 0.90f, float restitution = 0.30f,
										 glm::vec3 inertia = glm::vec3(0.0f, 0.0f, 0.0f));

		static void AddPivotConstraint(Rigidbody& rigidbody, btVector3 pivot);

	};

}
