#pragma once
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Renderer/FpsCamera.h"
#include "LukkelEngine/Renderer/Renderer.h"

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
		const s_ptr<FpsCamera> getCamera() const { return m_Camera; }

		Entity createEntity(const std::string& name = std::string());
		Entity createEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void destroyEntity(Entity entity);
		void createDynamicWorld();

	// TODO: Fix access
	public:
		bool m_IsRunning = false, m_IsPaused = false;
		int m_Frames = 0;
		Timer m_Timer;

		entt::registry m_Registry;
		std::unordered_map<UUID, entt::entity> m_EntityMap;

		s_ptr<FpsCamera> m_Camera;
		s_ptr<Renderer> m_Renderer;

		// btDiscreteDynamicsWorld* m_World = nullptr;
		
		friend class Entity;
	};
}