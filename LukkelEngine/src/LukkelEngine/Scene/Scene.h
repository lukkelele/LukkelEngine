#pragma once
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Renderer/FpsCamera.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Physics/World.h"

#include "entt/entt.hpp"
#include "LukkelEngine/Debug/Debugger.h"

namespace LukkelEngine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void onUpdate(float ts);
		void onImGuiRender();
		const s_ptr<FpsCamera> getCamera() const { return m_Camera; }

		Entity getEntityWithUUID(UUID uuid);
		Entity findEntity(std::string_view name);
		Entity createEntity(const std::string& name);
		Entity createEntityWithUUID(UUID uuid, const std::string& name);
		void destroyEntity(Entity entity);

		bool isRunning() const { return m_IsRunning; }
		void pause(bool paused) { m_IsPaused = paused; }

		template<typename T>
		void onComponentAdded(Entity wObject, T& component);

	public:
		bool m_IsRunning = false, m_IsPaused = false;
		int m_Frames = 0;
		Timer m_Timer;

		entt::registry m_Registry;
		std::unordered_map<UUID, entt::entity> m_EntityMap;

		s_ptr<FpsCamera> m_Camera;
		s_ptr<Renderer> m_Renderer;
		s_ptr<World> m_World;
	};

}