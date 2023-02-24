#pragma once
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Components.h"

#include "entt/entt.hpp"

namespace LukkelEngine {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene); // Circular dependency
		Entity(const Entity& other) = default;

		template<typename T, typename... ARGS>
		T& addComponent(ARGS&&... args)
		{
			T& component = m_Scene->m_Registry.emblace<T>(m_EntityHandle, std::forward<ARGS>(args)...);
			return component;
		}

		template<typename T>
		T& getComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		T& hasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void removeComponent()
		{
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		UUID getUUID() { return getComponent<IDComponent>().ID; }
		const std::string& GetName() { return getComponent<TagComponent>().Tag; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};

}