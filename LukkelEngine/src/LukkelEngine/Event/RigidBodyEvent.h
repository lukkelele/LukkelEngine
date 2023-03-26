#pragma once
#include "LukkelEngine/Event/Event.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {


	class RigidbodyEvent : public Event
	{
	public:
		btRigidBody* GetRigidbody() const { return m_Rigidbody; }

	protected:
		btRigidBody* m_Rigidbody = nullptr;
	};


	class LinearVelocityModificationEvent : public RigidbodyEvent
	{
	public:
		LinearVelocityModificationEvent(btRigidBody* rigidbody, glm::vec3 newVelocity)
			: m_LinearVelocity(newVelocity) { m_Rigidbody = rigidbody; }

	private:
		glm::vec3 m_LinearVelocity{ 0.0f, 0.0f, 0.0f };
	};

}