#pragma once
#include "LukkelEngine/Core/Base.h"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "glm/glm.hpp"


namespace LukkelEngine {

	struct RigidBodyComponent
	{
		btVector3 pos{ 0.0f, 0.0f, 0.0f };
		btVector3 dimensions{ 1.0f, 1.0f, 1.0f };
		btCollisionShape* shape = nullptr;
		btRigidBody* rigidBody = nullptr;
		btDefaultMotionState* motionState = nullptr;

		btScalar mass = 1.0f;
		float scale = 1.0f;
		float friction = 1.0f;
		float restitution = 0.20f;
		btVector3 inertia{ 0.0f, 0.0f, 0.0f };
		btVector3 linearVelocity{ 1.0f, 0.0f, 0.0f };
		btVector3 angularVelocity{ 0.0f, 0.0f, 0.0f };

		enum class BodyType { STATIC, DYNAMIC };
		BodyType bodyType = BodyType::STATIC;

		const btQuaternion quat0{ 0.0f ,0.0f, 0.0f, 1.0f }; // Reused for 0 degree transforms

		RigidBodyComponent(btVector3& dimensions, btVector3& offset, float mass = 1.0f)
			: dimensions(dimensions), mass(mass)
		{
			shape = new btBoxShape(dimensions);
			motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), offset));
			shape->calculateLocalInertia(mass, inertia);
			btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, motionState, shape, inertia);
			rigidBody = new btRigidBody(boxBodyConstructionInfo);
			rigidBody->setFriction(friction);
			rigidBody->setRestitution(restitution);
			// syncPosition();
		}

		void printPosition()
		{
			auto masspos = rigidBody->getCenterOfMassPosition();
			auto body = rigidBody;
			LKLOG_TRACE("Mass position: ({0}, {1}, {2})  | Mass: {3} ", masspos.getX(), masspos.getY(), masspos.getZ(), mass);
			LKLOG_TRACE("RigidbodyComponent: ({0}, {1}, {2}) | Mass : {3} ", pos.getX(), pos.getY(), pos.getZ(), mass);
		}

		// Takes center of mass and not in the edges
		void syncPosition()
		{
			btVector3 masspos = rigidBody->getCenterOfMassPosition();
			// LKLOG_WARN("Origin: ({0}, {1}, {2}),",  masspos.getX(), masspos.getY(), masspos.getZ());
			pos = masspos;
		}

		glm::mat4 getModelTransform(float scale = 1.0f)
		{
			btTransform transform(rigidBody->getWorldTransform());
			btVector3 translate = transform.getOrigin();
			transform.setOrigin(pos);
			// transform.setOrigin(translate);
			btVector3 masspos = rigidBody->getCenterOfMassPosition();
			// LKLOG_WARN("Origin: ({0}, {1}, {2}),",  masspos.getX(), masspos.getY(), masspos.getZ());
			rigidBody->setWorldTransform(transform);
			rigidBody->getMotionState()->setWorldTransform(transform);
			btQuaternion rotation = transform.getRotation();

			glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), rotation.getAngle(),
				glm::vec3(rotation.getAxis().getX(), rotation.getAxis().getY(), rotation.getAxis().getZ()));

			glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
			glm::mat4 transMat = glm::translate(glm::mat4(1.0f), glm::vec3(translate.getX(), translate.getY(), translate.getZ()));
			glm::mat4 modelMatrix = transMat * rotMat * scaleMat;
			return modelMatrix;
		}
	};

	struct RigidBodyComponent2D
	{
		glm::vec2 pos{ 0.0f, 0.0 };
		glm::vec2 dimensions{ 1.0f, 1.0 };
		btScalar mass = 1.0f;
		float scale = 1.0f;
		float friction = 1.0f, restitution = 0.20f;
		btCollisionShape* shape = nullptr;
		glm::vec2 inertia{ 0.0f, 0.0f };
		btRigidBody* rigidBody = nullptr;
		btDefaultMotionState* motionState = nullptr;
	};

}