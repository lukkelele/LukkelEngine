#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Physics/Body/RigidBody.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Components.h"

#include "entt/entt.hpp"


namespace LukkelEngine {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 binormal;
		glm::vec2 texcoord;
	};

	class Entity
	{
	public:
		Entity() = default;
		Entity(Mesh mesh, RigidBody rigidBody);
		Entity(entt::entity handle, Scene* scene);
		~Entity() {}

		void bind();
		void onUpdate(float ts, glm::mat4 viewProj);
		void remove();

		glm::mat4 getTransform(glm::mat4& viewProj);

		UUID getUUID() { return getComponent<IDComponent>().ID; }
		const std::string& getName() { return getComponent<TagComponent>().tag; }

		template<typename T, typename... ARGS>
		T& addComponent(ARGS&&... args)
		{
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<ARGS>(args)...);
			m_Scene->onComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		bool hasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		T& getComponent()
		{
			if (hasComponent<T>())
				return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		void removeComponent()
		{
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		// template<typename T>
		template<typename T, typename... ARGS>
		void addExistingComponent(T) 
		{
			m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<ARGS>(args)...);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		
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
		int m_ID; // Rigidbody identifier
		Scene* m_Scene = nullptr;

		s_ptr<Mesh> m_Mesh = nullptr;
		s_ptr<RigidBody> m_RigidBody = nullptr;

		glm::vec3 m_Position{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_Scale{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
		glm::quat m_Rotation{ 1.0f, 0.0f, 0.0f, 0.0f };

		glm::vec3 m_Inertia{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_LinearVelocity{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_AngularVelocity{ 0.0f, 0.0f, 0.0f };
	};

}
