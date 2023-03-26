#pragma once
#include "LukkelEngine/Physics/Rigidbody.h"
#include "LukkelEngine/Physics/Constraints.h"

#include <set>
#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	/* Forward declaration */
	class Camera;
	class Entity;
	
	// typedef std::pair<Entity, Entity> CollisionPair;
	typedef std::pair<const btRigidBody*, const btRigidBody*> CollisionPair;
	typedef std::set<CollisionPair> CollisionPairs;

	// typedef std::pair<const Rigidbody*, const Rigidbody*> CollisionPair;

	class CollisionDetector
	{
	public:
		static void Collision(btPersistentManifold* manifold);
		static void Separation(btPersistentManifold* manifold);
		static std::pair<glm::vec3, glm::vec3> Raycast(const Camera& camera);
	};
}
