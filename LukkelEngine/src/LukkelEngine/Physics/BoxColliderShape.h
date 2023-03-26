#pragma once 
#include "LukkelEngine/Physics/ColliderShape.h"


namespace LukkelEngine {

	class RigidBodyFactory;

	class BoxColliderShape : public ColliderShape
	{
	public:
		BoxColliderShape(UUID& entityID, glm::vec3& dimensions, 
			glm::vec3& offset, float mass, glm::vec3& inertia, Rigidbody::Type rigidbodyType);
		~BoxColliderShape() = default;

		const char* GetShapeName() const override { return "BoxCollider"; }

	private:

	};

}
