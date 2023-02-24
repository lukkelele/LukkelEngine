#pragma once
#include <deque> // Temporary fix because unordered map bugs out

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/Timestep.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Renderer/FpsCamera.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Physics/Collider.h"
#include "LukkelEngine/Physics/Ground.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "entt/entt.hpp"

#define LK_WORLD_NEUTRAL 0
#define LK_WORLD_DYNAMIC 1
#define LK_WORLD_GRAVITY_DEFAULT btVector3(0.0f, -9.8f, 0.0f)
#define LK_WORLD_GRAVITY_SLOW btVector3(0.0f, -4.5f, 0.0f)
#define LK_WORLD_GRAVITY_SLOWER btVector3(0.0f, -1.5f, 0.0f)
#define LK_WORLD_GRAVITY_SLOWEST btVector3(0.0f, -0.5f, 0.0f)
#define LK_WORLD_GRAVITY_FAST btVector3(0.0f, -18.0f, 0.0f)


namespace LukkelEngine {

	class Scene
	{
	public:
		Scene();
		~Scene();

		void onUpdate(float ts);
		void onImGuiRender();
		bool isRunning() const { return m_IsRunning; }
		void pause(bool paused) { m_IsPaused = paused; }
		void addEntity(Entity &entity);
		void addCollider(btRigidBody* collider);
		std::deque<Entity*>& getEntities() { return m_Entities; }
		const s_ptr<FpsCamera> getCamera() const { return m_Camera; }
		void createDynamicWorld();

	private:
		bool m_IsRunning = false, m_IsPaused = false;
		int m_Frames = 0;

		Timer m_Timer;
		entt::registry m_Registry;
		std::deque<Entity*> m_Entities;
		s_ptr<FpsCamera> m_Camera;
		s_ptr<Renderer> m_Renderer;

		btDiscreteDynamicsWorld* m_World;
		Ground* ground; // REMOVE ME
	};
}