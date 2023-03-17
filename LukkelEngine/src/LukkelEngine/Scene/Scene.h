#pragma once
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Scene/SceneCamera.h"
#include "LukkelEngine/Editor/EditorCamera.h"
#include "LukkelEngine/Renderer/Renderer.h"

#include "entt/entt.hpp"
#include "LukkelEngine/Debug/Debugger.h"

namespace LukkelEngine {

	class Entity;
	class World;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void onUpdate(float ts);
		void onImGuiRender();
		const s_ptr<Camera> getCamera() const { return m_Camera; }

		Entity getEntityWithUUID(UUID uuid);
		Entity findEntity(std::string_view name);
		Entity createEntity(const std::string& name);
		Entity createEntityWithUUID(UUID uuid, const std::string& name);
		void destroyEntity(Entity entity);

		s_ptr<World> getWorld() { return m_World; }
		bool isRunning() const { return m_IsRunning; }
		void pause(bool paused);

		void switchCamera();

		template<typename T>
		void onComponentAdded(Entity entity, T& component);

	public:
		bool m_IsRunning = false;
		bool m_Paused = false;
		int m_Frames = 0;
		Timer m_Timer;

		entt::registry m_Registry;
		std::unordered_map<UUID, entt::entity> m_EntityMap;

		s_ptr<Renderer> m_Renderer;
		s_ptr<World> m_World;

		// s_ptr<EditorLayer> m_EditorLayer; // FIXME
		s_ptr<SceneCamera> m_Camera;
		s_ptr<EditorCamera> m_EditorCamera;
	};

}