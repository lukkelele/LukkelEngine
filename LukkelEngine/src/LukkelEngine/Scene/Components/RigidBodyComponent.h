#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Debug/Debugger.h"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "glm/glm.hpp"


namespace LukkelEngine {

	struct RigidBodyComponent
	{
		btVector3 position{ 0.0f, 0.0f, 0.0f };
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

		glm::mat4 getModelTransform()
		{
			btTransform transform = rigidBody->getWorldTransform();
			position = transform.getOrigin();
			glm::mat4 rotationMatrix = getRotation(transform);
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
			glm::mat4 translationMatrix = getTranslation(transform);
			glm::mat4 modelTransform = translationMatrix * rotationMatrix * scaleMatrix;

			return modelTransform;
		}

		glm::mat4 getTranslation(btTransform worldTransform)
		{
			btTransform transform(rigidBody->getWorldTransform());
			btVector3 translate = transform.getOrigin();
			glm::mat4 translation = glm::translate(glm::mat4(1.0f),
										glm::vec3(translate.getX(), translate.getY(), translate.getZ()));
			return translation;
		}

		glm::mat4 getRotation(btTransform worldTransform)
		{
			btQuaternion rot = worldTransform.getRotation();
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rot.getAngle(),
				glm::vec3(rot.getAxis().getX(), rot.getAxis().getY(), rot.getAxis().getZ()));

			return rotation;
		}

		btRigidBody* getRigidBody() { return rigidBody; }

		void updateBodyProperties(glm::vec3& pos)
		{
			Debugger::printVec3(position, "Rigidbody pos");
			pos = { position.getX(), position.getY(), position.getZ() };
		}
		
		// void setPosition(glm::vec3 newPos) { position = btVector3{ newPos.x, newPos.y, newPos.z }; }
		glm::vec3 getPosition() { return glm::vec3(position.getX(), position.getY(), position.getZ()); }
			
	};

}