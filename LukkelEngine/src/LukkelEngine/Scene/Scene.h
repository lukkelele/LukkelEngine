#pragma once
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Scene/SceneCamera.h"
#include "LukkelEngine/Editor/EditorCamera.h"
#include "LukkelEngine/Renderer/Renderer.h"

#include "entt/entt.hpp"
#include "LukkelEngine/Debug/Debugger.h"

#define getEntityWithRigidbody(rb) Scene::getActiveScene()->getEntityWithUUID((uint64_t)rb->getUserPointer())


namespace LukkelEngine {

	class Entity;
	class World;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(float ts);
		void OnImGuiRender();
		const s_ptr<Camera> getCamera() const { return m_Camera; }

		Entity getEntityWithUUID(UUID uuid);
		Entity FindEntity(std::string_view name);
		Entity CreateEntity(const std::string& name);
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name);
		void DestroyEntity(Entity entity);

		s_ptr<World> GetWorld() { return m_World; }
		bool IsRunning() const { return m_IsRunning; }
		void Pause(bool paused);

		void SwitchCamera();

		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		static Scene* GetActiveScene() { return s_ActiveScene; }

	public:
		static Scene* s_ActiveScene;
		bool m_IsRunning = false;
		bool m_Paused = false;
		int m_Frames = 0;
		Timer m_Timer;

		entt::registry m_Registry;
		std::unordered_map<UUID, entt::entity> m_EntityMap;

		s_ptr<Renderer> m_Renderer;
		s_ptr<World> m_World;

		s_ptr<SceneCamera> m_Camera;
		s_ptr<EditorCamera> m_EditorCamera;
	};

}