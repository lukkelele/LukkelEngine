#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "LukkelEngine/Model/Mesh.h"
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

	class WorldObject
	{
	public:
		WorldObject(Mesh mesh, RigidBody rigidBody);
		WorldObject(entt::entity handle, Scene* scene);
		WorldObject(const WorldObject& other) = default;
		~WorldObject();

		void bind();
		void onUpdate(float ts, glm::mat4 viewProj);
		void remove();

		glm::mat4 getTransform(glm::mat4& viewProj);

		UUID getUUID() { return getComponent<IDComponent>().ID; }
		const std::string& getName() { return getComponent<TagComponent>().tag; }

		// 'Casts' on the fly
		operator bool() const { return m_ObjectHandle != entt::null; }
		operator entt::entity() const { return m_ObjectHandle; }
		operator uint32_t() const { return (uint32_t)m_ObjectHandle; }
		bool operator!=(const WorldObject& other) const { return !(*this == other); }
		bool operator==(const WorldObject& other) const { return m_ObjectHandle == other.m_ObjectHandle && m_Scene == other.m_Scene; }

		template<typename T, typename... ARGS>
		T& addComponent(ARGS&&... args)
		{
			T& component = m_Scene->m_Registry.emplace<T>(m_ObjectHandle, std::forward<ARGS>(args)...);
			m_Scene->onComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		bool hasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_ObjectHandle);
		}

		template<typename T>
		T& getComponent()
		{
			if (hasComponent<T>())
				return m_Scene->m_Registry.get<T>(m_ObjectHandle);
		}

		template<typename T>
		void removeComponent()
		{
			m_Scene->m_Registry.remove<T>(m_ObjectHandle);
		}

		// template<typename T>
		template<typename T, typename... ARGS>
		void addExistingComponent(T) 
		{
			m_Scene->m_Registry.emplace<T>(m_ObjectHandle, std::forward<ARGS>(args)...);
		}


	private:
		entt::entity m_ObjectHandle{ entt::null };
		int m_ID; // Rigidbody identifier
		Scene* m_Scene = nullptr;

		u_ptr<Mesh> m_Mesh;
		u_ptr<RigidBody> m_RigidBody;

		glm::vec3 m_Position{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_Scale{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
		glm::quat m_Rotation{ 1.0f, 0.0f, 0.0f, 0.0f };

		glm::vec3 m_Inertia{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_LinearVelocity{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_AngularVelocity{ 0.0f, 0.0f, 0.0f };
	};

}
