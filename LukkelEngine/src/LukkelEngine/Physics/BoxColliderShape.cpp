#include "LKpch.h"
#include "LukkelEngine/Physics/BoxColliderShape.h"
#include "LukkelEngine/Physics/RigidbodyFactory.h"


namespace LukkelEngine {

		BoxColliderShape::BoxColliderShape(UUID& entityID, glm::vec3& dimensions, 
			glm::vec3& offset, float mass, glm::vec3& inertia, Rigidbody::Type rigidbodyType)
		{
			// TODO: Add restitution and friction as constructor arguments
			float restitution = 0.3f;
			float friction = 1.0f;

			Rigidbody& rigidbody = RigidbodyFactory::CreateRigidbody(entityID, Rigidbody::Shape::Cube,
				rigidbodyType, dimensions, offset, mass, friction, restitution, inertia);

			m_Rigidbody = rigidbody;
		}

}
