#pragma once
#include "LukkelEngine/Event/Event.h"
#include "LukkelEngine/Physics/Body/Constraints.h"
#include "LukkelEngine/Physics/Body/Rigidbody.h"
#include "LukkelEngine/Physics/World.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	/**
	 * @brief Base event for hit detection and collision type events
	*/
	class HitDetectionEvent : public Event
	{
	public:
		HitDetectionEvent(const btRigidBody*& body1, const btRigidBody*& body2)
			: m_CollisionBody1(body1), m_CollisionBody2(body2)
		{
		}

	protected:
		const btRigidBody* m_CollisionBody1;
		const btRigidBody* m_CollisionBody2;
		glm::vec4 m_CollisionColor = Color::Black;
	};


	class CollisionEvent : public HitDetectionEvent 
	{
	public:
		CollisionEvent(const btRigidBody*& body1, const btRigidBody*& body2)
			: HitDetectionEvent(body1, body2)
		{
		}

		EventType getEventType() const { return EventType::Collision; }
		const char* getName() const { return "CollisionEvent"; }

		bool handleEvent()
		{
			// Exit event if either the first or second body doesn't exist
			if (!m_CollisionBody1 || !m_CollisionBody2) 
				return true;

			// Get the entities hit and set their color
			Entity& entity1 = Scene::getActiveScene()->getEntityWithUUID((uint64_t)m_CollisionBody1->getUserPointer());
			Entity& entity2 = Scene::getActiveScene()->getEntityWithUUID((uint64_t)m_CollisionBody2->getUserPointer());
			auto& material1 = entity1.getComponent<Material>();
			auto& material2 = entity2.getComponent<Material>();
			glm::vec4 color1 = material1.getCachedMaterialColor();
			glm::vec4 color2 = material2.getCachedMaterialColor();
			// If the body is not of a static type
			auto type1 = entity1.getComponent<Rigidbody>().getType();
			auto type2 = entity2.getComponent<Rigidbody>().getType();

			if (type1 != Rigidbody::Type::STATIC && type2 != Rigidbody::Type::STATIC)
			{
				// LKLOG_TRACE("(Material 1) Cached -> ({0}, {1}, {2})", color1.x, color1.y, color1.z);
				// LKLOG_TRACE("(Material 2) Cached -> ({0}, {1}, {2})", color2.x, color2.y, color2.z);
				if (material1.getMaterialColor() != m_CollisionColor) material1.setMaterialColor(Color::Black);
				if (material2.getMaterialColor() != m_CollisionColor) material2.setMaterialColor(Color::Black);
			}

			return true;
		}
	};

	class SeparationEvent : public HitDetectionEvent
	{
	public:
		SeparationEvent(const btRigidBody*& body1, const btRigidBody*& body2)
			: HitDetectionEvent(body1, body2)
		{
		}

		EventType getEventType() const { return EventType::Separation; }
		const char* getName() const { return "SeparationEvent"; }

		bool handleEvent()
		{
			// Exit event if either the first or second body doesn't exist
			if (!m_CollisionBody1 || !m_CollisionBody2) 
				return true;

			Entity& entity1 = Scene::getActiveScene()->getEntityWithUUID((uint64_t)m_CollisionBody1->getUserPointer());
			Entity& entity2 = Scene::getActiveScene()->getEntityWithUUID((uint64_t)m_CollisionBody2->getUserPointer());
			auto& material1 = entity1.getComponent<Material>();
			auto& material2 = entity2.getComponent<Material>();

			auto type1 = entity1.getComponent<Rigidbody>().getType();
			auto type2 = entity2.getComponent<Rigidbody>().getType();

			// Revert the colors
			if (type1 != Rigidbody::Type::STATIC && type2 != Rigidbody::Type::STATIC)
			{
				if (material1.getMaterialColor() == m_CollisionColor) material1.setLastMaterialColor();
				if (material2.getMaterialColor() == m_CollisionColor) material2.setLastMaterialColor();
			}

			return true;
		}
	};

}