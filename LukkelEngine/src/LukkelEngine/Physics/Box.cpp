#include "LKpch.h"
#include "LukkelEngine/Physics/Box.h"


namespace LukkelEngine {

	namespace CollisionBody {

		/**
		 * @brief Create new box body
		 * @param length is the length of the box
		 * @param height is the height of the box
		 * @param depth is the depth of the box
		 * @param xOffset is the offset in x direction
		 * @param yOffset is the offset in y direction
		*/
		Box::Box(float length, float height, float depth,
				 float xOffset, float yOffset, float zOffset,
				 btScalar mass, btVector3 inertia, float friction, float restitution)
		{
			m_Shape = new btBoxShape(btVector3(length, height, depth));
			m_MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
													 btVector3(xOffset, yOffset, zOffset)));
			m_Mass = mass;
			m_Inertia = inertia;
			m_Shape->calculateLocalInertia(m_Mass, m_Inertia);
			btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(m_Mass, m_MotionState, m_Shape, m_Inertia);

			m_RigidBody = new btRigidBody(boxBodyConstructionInfo);
			m_RigidBody->setFriction(friction);
			m_RigidBody->setRestitution(restitution);
		}

		Box::~Box()
		{
			LKLOG_WARN("Deleting box body");
			delete m_Shape;
			delete m_MotionState;
		}

		// void Box::reposition(btVector3 pos, btVector3 orientation)
		// {
		// 	btTransform initialTransform;
		// 	btQuaternion quat(orientation.getX(), orientation.getY(), orientation.getZ(), 1);
		// 	initialTransform.setOrigin(pos);
		// 	initialTransform.setRotation(quat);

		// 	m_RigidBody->setWorldTransform(initialTransform);
		// 	m_MotionState->setWorldTransform(initialTransform);
		// }

	}

}