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
		m_Camera->updateDirection();
		glm::mat4 viewProj = m_Camera->getViewProjection();

		// float distance = 40.0f;
		// RaycastResult res;
		// btVector3 pos = Vector3::btVec3(m_Camera->m_Position);
		// btVector3 dir = Vector3::btVec3(m_Camera->m_ForwardDir) * distance;
		// bool hitreg = m_World->raycast(res, pos, dir);

		entt::basic_view meshes = m_Registry.view<MeshComponent>();
		for (entt::entity e : meshes)
		{	
			Entity entity = { e, this };
			MeshComponent& mesh = entity.getComponent<MeshComponent>();
			RigidBodyComponent& body = entity.getComponent<RigidBodyComponent>();
			// MaterialComponent& material = entity.getComponent<MaterialComponent>();

			glm::mat4 modelTransform = body.getModelTransform(ts);
			// Move this
			mesh.shader->bind();
			mesh.shader->setUniformMat4f("u_Model", modelTransform);
			mesh.shader->setUniformMat4f("u_ViewProj", viewProj);

			m_Renderer->draw(*mesh.va, *mesh.ib, *mesh.shader);
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
		void Scene::onComponentAdded(Entity entity, T& component)
		{
			// static assert	
		}

		template<>
		void Scene::onComponentAdded<RigidBodyComponent>(Entity entity, RigidBodyComponent& component)
		{
			LKLOG_INFO("Adding rigid body to world");
			m_World->addRigidBodyToWorld(component.rigidBody);
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

}