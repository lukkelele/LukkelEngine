#pragma once
#include "LukkelEngine/Event/Event.h"
#include "LukkelEngine/Physics/Body/Constraints.h"
#include "LukkelEngine/Physics/Body/Rigidbody.h"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>


namespace LukkelEngine {


	class CollisionEvent : public Event
	{
	public:
		CollisionEvent(Rigidbody& rigidbody1, Rigidbody& rigidbody2)
			: m_CollisionBody1(&rigidbody1), m_CollisionBody2(&rigidbody2)
		{
		}

		// Either 1 or 2
		Rigidbody& getCollisionBody(uint8_t bodyNumber = 1)
		{
			if (bodyNumber < 1 || bodyNumber > 2) return;
			if (bodyNumber == 1) return *m_CollisionBody1;
			if (bodyNumber == 2) return *m_CollisionBody2;
		}


		bool handleEvent()
		{
			return true;
		}

	protected:
		Rigidbody* m_CollisionBody1;
		Rigidbody* m_CollisionBody2;
		btCollisionDispatcher* m_Dispatcher;

	};


}