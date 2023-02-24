#pragma once

#include "LukkelEngine/Core/Base.h"
#include "btBulletDynamicsCommon.h"


namespace LukkelEngine {

	namespace CollisionBody {

		class Collider
		{
		public:
			Collider() = default;
			virtual ~Collider() = default;

			btRigidBody* getRigidBody() { return m_RigidBody; }
			void setRestitution(float r) { m_RigidBody->setRestitution(r); }
			void setFriction(float f) { m_RigidBody->setFriction(f); }

			// virtual void reposition(btVector3 pos, btVector3 orientation); // = 0;
		public:
			btRigidBody* m_RigidBody;
			btCollisionShape* m_Shape;
			btScalar m_Mass = 0.0f;
			float m_Friction = 1.0f;
			float m_Restitution = 0.5f;
			btVector3 m_Inertia = { 0, 0, 0 };
			btDefaultMotionState* m_MotionState;
		};

	}
}