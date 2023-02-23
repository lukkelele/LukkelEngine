#pragma once

#include <deque> // Temporary fix because unordered map bugs out

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/Timestep.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Renderer/FpsCamera.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Physics/WorldPhysics.h"

#include "entt/entt.hpp"

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

		WorldPhysics m_Physics;
		btDiscreteDynamicsWorld* m_World;

	};
}