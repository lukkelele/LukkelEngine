#include "LKpch.h"
#include "LukkelEngine/Physics/Body/RigidBody.h"
#include "LukkelEngine/Physics/World.h"

namespace LukkelEngine {


	RigidBody::RigidBody(glm::vec3 dimensions, glm::vec3 offset, float mass,
				  RigidBody::Type bodyType, float friction, float restitution, glm::vec3 inertia)
	{
		btVector3 dims{ dimensions.x, dimensions.y, dimensions.z };
		btVector3 off{ offset.x, offset.y, offset.z };
		m_Dimensions = dims;
		m_Shape = new btBoxShape(dims);
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(off);

		m_MotionState = new MotionState(transform);
		m_MotionState->setWorldTransform(transform);
		m_Shape->calculateLocalInertia(m_Mass, m_Inertia);
		btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, m_MotionState, m_Shape, m_Inertia);

		m_RigidBody = new btRigidBody(boxBodyConstructionInfo);
		m_RigidBody->setFriction(m_Friction);
		m_RigidBody->setRestitution(m_Restitution);
		m_RigidBody->forceActivationState(DISABLE_DEACTIVATION);
	}

	void RigidBody::onUpdate(float ts)
	{
	}

	void RigidBody::moveBody(glm::vec3 translation)
	{
		m_Position = {translation.x, translation.y, translation.z};
		btTransform transform;
		btMotionState* motionState = m_RigidBody->getMotionState();
		motionState->getWorldTransform(transform);
		transform.setOrigin(m_Position);
		motionState->setWorldTransform(transform);
		m_RigidBody->setCenterOfMassTransform(transform);
	}


	void RigidBody::setLinearVelocity(glm::vec3& linearVelocity)
	{

		m_LinearVelocity = { linearVelocity.x, linearVelocity.y, linearVelocity.z };
		m_RigidBody->setLinearVelocity(m_LinearVelocity);
	}

	void RigidBody::setWorldTransform(glm::mat4& transform)
	{
	}

	btTransform RigidBody::getWorldTransform()
	{ 
		if (m_RigidBody)
		{
			return m_RigidBody->getWorldTransform();
		}
		else
		{
			LKLOG_CRITICAL("getWorldTransform() -> rigidbody doesn't exist");
		}
	}

	std::pair<glm::vec3, glm::quat> RigidBody::getPosAndRotation()
	{		
		btTransform transform = getWorldTransform();
		btVector3 position = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();
		glm::vec3 pos(position.x(), position.y(), position.z());
		glm::mat4 rot = glm::mat4_cast(glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ()));
		return std::make_pair(pos, rot);
	}

	void RigidBody::addPivotConstraint(glm::vec3 pivot)
	{
		btVector3 p = { pivot.x, pivot.y, pivot.z };
		btTypedConstraint* pivotConstraint = new btPoint2PointConstraint(*getRigidBody(), p);
		//World::getCurrentWorld().registerEvent(new ConstraintAddedEvent(getRigidBody(), ConstraintType::Pivot));
		World::getCurrentWorld().registerEvent(new ConstraintAddedEvent(pivotConstraint, ConstraintType::Pivot));
	}



}