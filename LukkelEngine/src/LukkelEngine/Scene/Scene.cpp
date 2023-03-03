#include "LKpch.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Scene/Entity.h"

#include "glm/glm.hpp"

#include "LukkelEngine/Debug/GLDebugDrawer.h"

namespace LukkelEngine {


	Scene::Scene()
	{
		m_Camera = create_s_ptr<FpsCamera>(45.0f, 0.010f, 1000.0f);
		m_Camera->setPosition(glm::vec3(0.0f, 15.0f, -46.0f));
		m_Camera->setScene(this);

		m_World = create_s_ptr<World>();
		m_World->initPhysics(this);
	}
	
	Scene::~Scene()
	{
	}

	Entity Scene::createEntity(const std::string& name)
	{
		Entity entity = createEntityWithUUID(UUID(), name);
		return entity;
	}

	void Scene::destroyEntity(Entity entity)
	{
		m_EntityMap.erase(entity.getUUID());
		m_Registry.destroy(entity);
		LKLOG_CRITICAL("Entity successfully deleted");
	}

	Entity Scene::createEntityWithUUID(UUID uuid, const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.addComponent<IDComponent>(uuid);
		TagComponent& tag = entity.addComponent<TagComponent>();
		tag.tag = name.empty() ? "Entity" : name;
		m_EntityMap[uuid] = entity;
		return entity;
	}

	void Scene::onUpdate(float ts)
	{
		m_World->onUpdate(ts);
		m_Camera->onUpdate(ts);

		glm::mat4 viewProj = m_Camera->getViewProjection();

		auto meshes = m_Registry.view<Mesh>();
		for (auto e : meshes)
		{	
			Entity entity = { e, this };
			auto& mesh = entity.getComponent<Mesh>();
			mesh.onUpdate(ts, viewProj);

			m_Renderer->draw(mesh);
		}

		m_World->m_World->debugDrawWorld();
	}

	void Scene::onImGuiRender()
	{
		m_Camera->onImGuiRender();
	}

	Entity Scene::getEntityWithUUID(UUID uuid)
	{
		if (m_EntityMap.find(uuid) != m_EntityMap.end())
			return { m_EntityMap.at(uuid), this };
		return { };
	}

	Entity Scene::findEntity(std::string_view name)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto entity : view)
		{
			const TagComponent& tc = view.get<TagComponent>(entity);
			if (tc.tag == name)
				return Entity{ entity, this };
		}
		return {};
	}

	template<typename T>
	void Scene::add(T& item)
	{
	}

		template<>
		void Scene::add<Mesh>(Mesh& mesh)
		{
			m_Meshes.push_back(mesh);
		}

	template<typename T>
		void Scene::onComponentAdded(Entity entity, T& component)
		{
			// static assert	
		}

		template<>
		void Scene::onComponentAdded<RigidBodyComponent>(Entity entity, RigidBodyComponent& component)
		{
			LKLOG_TRACE("Adding rigid body to world");
			m_World->addRigidBodyToWorld(component.rigidBody);
		}

		template<>
		void Scene::onComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
		{
		}

		template<>
		void Scene::onComponentAdded<MeshComponent>(Entity entity, MeshComponent& component)
		{
		}

		template<>
		void Scene::onComponentAdded<MaterialComponent>(Entity entity, MaterialComponent& component)
		{
		}

		template<>
		void Scene::onComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component)
		{
		}

		template<>
		void Scene::onComponentAdded<Mesh>(Entity entity, Mesh& component)
		{
			m_World->addRigidBodyToWorld(component.getRigidBody());
			LKLOG_INFO("Added rigid body to world");
		}



}