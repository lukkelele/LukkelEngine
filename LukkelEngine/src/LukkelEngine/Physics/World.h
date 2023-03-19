#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Debug/Debugger.h"
#include "LukkelEngine/Debug/PhysicsDebugger.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Event/Event.h"
#include "LukkelEngine/Physics/Collision.h"

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletSoftBody/btSoftBody.h>
#include <bullet3/src/BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <CommonCallbacks.h>
#include <entt/entt.hpp>

#define LK_WORLD_NEUTRAL 0
#define LK_WORLD_DYNAMIC 1
#define LK_WORLD_GRAVITY_DEFAULT btVector3(0.0f, -9.8f, 0.0f)
#define LK_WORLD_GRAVITY_SLOW    btVector3(0.0f, -4.5f, 0.0f)
#define LK_WORLD_GRAVITY_SLOWER  btVector3(0.0f, -1.5f, 0.0f)
#define LK_WORLD_GRAVITY_SLOWEST btVector3(0.0f, -0.5f, 0.0f)
#define LK_WORLD_GRAVITY_FAST    btVector3(0.0f, -18.0f, 0.0f)
#define LK_WORLD_REGISTER_EVENT(x) World::getCurrentWorld().registerEvent(x)
#define LK_WORLD_ENTITY_COUNT World::getCurrentWorld().getWorldEntityCount()


namespace LukkelEngine {

	class Scene;

	struct RaycastResult 
	{
		btRigidBody* body;
		btVector3 hitPoint;
	};

	class World
	{
	public:
		World();
		~World();

		void onUpdate(float ts);
		void onEvent(Event& event);
		void initPhysics(Scene* scene);
		void shutdownPhysics();
		void stepSimulation(float ts);
		void pause(bool paused) { m_Paused = paused; };
		void handleEvents();
		void registerEvent(Event* event);

		template<typename T>
		void addRigidbodyToWorld(T& rigidbody);

		bool pickBody(const Camera& camera, float distance);
		void addConstraint(Constraint& constraint) { m_DynamicWorld->addConstraint(constraint.getConstraint()); }
		void removeConstraint(Constraint& constraint) { m_DynamicWorld->removeConstraint(constraint.getConstraint()); }
		void createPickingConstraint(float x, float y);
		void removePickConstraint();
		void checkCollisions();
		uint64_t getWorldEntityCount() { return s_EntitiesInWorld; }

		bool mouseButtonCallback(int button, int state, float x, float y);
		bool mouseMoveCallback(float x, float y);
		void resetMousePick();

		static Entity& getEntity(Rigidbody& rigidbody);
		static World& getCurrentWorld() { return *m_CurrentWorld; }

	private:
		btDiscreteDynamicsWorld* m_DynamicWorld = nullptr;
		btBroadphaseInterface* m_BroadphaseInterface = nullptr;
		btDefaultCollisionConfiguration* m_CollisionConfig = nullptr;
		btCollisionDispatcher* m_Dispatcher = nullptr;
		btSequentialImpulseConstraintSolver* m_SequentialConstraintSolver = nullptr;

		b3MouseButtonCallback m_PrevMouseButtonCallback = 0;
		b3MouseMoveCallback m_PrevMouseMoveCallback = 0;

		btRigidBody* m_PickedBody = nullptr;
		Entity m_PickedEntity{};
		btTypedConstraint* m_PickedConstraint = nullptr;
		btVector3 m_HitPos{};
		btVector3 m_OldPickingPos{};
		btScalar m_OldPickingDist{};
		int m_SavedState = 0;

		CollisionPairs m_LastCollisionPairs;
		
		std::vector<Event*> m_Events;
		bool m_Paused = false;

		static World* m_CurrentWorld;
		static uint64_t s_EntitiesInWorld;
		Scene* m_Scene = nullptr;
	};
}
