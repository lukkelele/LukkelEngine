#pragma once

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Debug/Debugger.h"
#include "LukkelEngine/Physics/Body/RigidBody.h"
#include "LukkelEngine/Physics/Body/MotionState.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	class RigidBodyFactory
	{
	public:
		RigidBodyFactory();
		~RigidBodyFactory() = default;
		
		static RigidBody createRigidBody(glm::vec3 dimensions, glm::vec3 offset, float mass,
										  RigidBody::Type bodyType, float friction = 0.90f,
										  float restitution = 0.30f, glm::vec3 inertia = glm::vec3(0.0f, 0.0f, 0.0f));

		// static void removeRigidBody(RigidBody& rigidbody);
	};

}
