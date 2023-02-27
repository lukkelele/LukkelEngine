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
		float friction = 1.0f;
		float restitution = 0.20f;
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
		glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 translation{ 0.0f, 0.0f, 0.0f };
		btVector3 inertia{ 0.0f, 0.0f, 0.0f };
		btVector3 linearVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 angularVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 offset;

		enum class BodyType { STATIC, DYNAMIC };
		BodyType bodyType = BodyType::STATIC;

		const btQuaternion quat0{ 0.0f ,0.0f, 0.0f, 1.0f }; // Reused for 0 degree transforms

		RigidBodyComponent() = default;
		RigidBodyComponent(btVector3& dimensions, btVector3& offset, float mass = 1.0f)
			: dimensions(dimensions), mass(mass), offset(offset)
		{
			shape = new btBoxShape(dimensions);
			motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), offset));
			shape->calculateLocalInertia(mass, inertia);
			btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, motionState, shape, inertia);
			rigidBody = new btRigidBody(boxBodyConstructionInfo);
			rigidBody->setFriction(friction);
			rigidBody->setRestitution(restitution);
		}

		glm::mat4 getModelTransform(float ts)
		{
			btTransform transform(rigidBody->getWorldTransform());
			auto dv = linearVelocity * ts / 100.0f;
			btVector3 translate = transform.getOrigin() + dv;
			transform.setOrigin(translate);
			btQuaternion rot = transform.getRotation();
			rigidBody->setWorldTransform(transform);
			rigidBody->getMotionState()->setWorldTransform(transform); // Affects velocity
			
			glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), rot.getAngle(),
				glm::vec3(rot.getAxis().getX(), rot.getAxis().getY(), rot.getAxis().getZ()) + rotation);

			glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
			glm::mat4 transMat= glm::translate(glm::mat4(1.0f), glm::vec3(translate.getX(), translate.getY(), translate.getZ()));
			glm::mat4 modelMatrix = transMat * rotMat * scaleMat;
			return modelMatrix;
		}


		void printPosition()
		{
			auto masspos = rigidBody->getCenterOfMassPosition();
			LKLOG_INFO("Mass position: ({0}, {1}, {2})  | Mass: {3} ", masspos.getX(), masspos.getY(), masspos.getZ(), mass);
			LKLOG_WARN("RigidbodyComponent: ({0}, {1}, {2}) | Mass : {3} ", pos.getX(), pos.getY(), pos.getZ(), mass);
		}

	};


}