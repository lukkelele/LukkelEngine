#pragma once

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Debug/Debugger.h"
#include "LukkelEngine/Physics/Body/Rigidbody.h"
#include "LukkelEngine/Physics/Body/MotionState.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	class RigidbodyFactory
	{
	public:
		RigidbodyFactory();
		~RigidbodyFactory() = default;
		
		static Rigidbody createRigidbody(glm::vec3 dimensions, glm::vec3 offset, float mass,
										  Rigidbody::RigidbodyType bodyType, float friction = 0.90f,
										  float restitution = 0.30f, glm::vec3 inertia = glm::vec3(0.0f, 0.0f, 0.0f));

		static Rigidbody createRigidbody(UUID id, glm::vec3 dimensions, glm::vec3 offset, float mass,
										  Rigidbody::RigidbodyType bodyType, float friction = 0.90f,
										  float restitution = 0.30f, glm::vec3 inertia = glm::vec3(0.0f, 0.0f, 0.0f));

		static void addPivotConstraint(Rigidbody& rigidbody, btVector3 pivot);
	};

}
