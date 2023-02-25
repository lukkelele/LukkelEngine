#include "LKpch.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Scene/Entity.h"

#include "glm/glm.hpp"


namespace LukkelEngine {

	Scene::Scene()
	{
		m_Camera = create_s_ptr<FpsCamera>(45.0f, 0.010f, 1000.0f);
		m_Camera->setPosition(glm::vec3(0.0f, 2.5f, -10.0f));
		createDynamicWorld();
	}
	
	Scene::~Scene()
	{
		delete m_World;
	}

	Entity Scene::createEntity(const std::string& name)
	{
		Entity entity = createEntityWithUUID(UUID(), name);
		return entity;
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
		m_Camera->onUpdate(ts);
		m_World->stepSimulation(ts);
		glm::mat4 viewProj = m_Camera->getViewProjection();

		entt::basic_view meshes = m_Registry.view<MeshComponent>();

		for (entt::entity e : meshes)
		{	
			Entity entity = { e, this };
			MeshComponent& mesh = entity.getComponent<MeshComponent>();
			RigidBody3DComponent& body3D = entity.getComponent<RigidBody3DComponent>();

			if (entity.getName() == "Cube1")
			{
				mesh.renderImGuiSettings();
			}

			auto meshTranslation = mesh.getTranslation();
			glm::mat4 modelTransform = body3D.getModelTransform(meshTranslation);

			mesh.updateOrientation(modelTransform, viewProj);
			body3D.printPosition();

			m_Renderer->draw(*mesh.va, *mesh.ib, *mesh.shader);
		}
	}

	void Scene::onImGuiRender()
	{
	}

	void Scene::createDynamicWorld()
	{
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();
		btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

		m_World = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
		m_World->setGravity(LK_WORLD_GRAVITY_SLOW);
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
		void Scene::onComponentAdded<RigidBody3DComponent>(Entity entity, RigidBody3DComponent& component)
		{
			LKLOG_WARN("Adding rigid body to dynamic world");
			m_World->addRigidBody(component.rigidBody);
		}

		template<>
		void Scene::onComponentAdded<MeshComponent>(Entity entity, MeshComponent& component)
		{
		}

		template<>
		void Scene::onComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component)
		{
		}
}