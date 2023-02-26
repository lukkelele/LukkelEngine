#include "LKpch.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Scene/Entity.h"

#include "glm/glm.hpp"

#include "GLDebugDrawer.h"

namespace LukkelEngine {

	GLDebugDrawer debugDrawer;

	Scene::Scene()
	{
		m_Camera = create_s_ptr<FpsCamera>(45.0f, 0.010f, 1000.0f);
		m_Camera->setPosition(glm::vec3(0.0f, 15.0f, -46.0f));
		
		// Set up physics
		createDynamicWorld();
		// Physics debugger
		debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
		m_World->setDebugDrawer(&debugDrawer);
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
		m_Entities.push_back(entity);
		return entity;
	}

	void Scene::onUpdate(float ts)
	{
		m_Camera->onUpdate(ts);
		glm::mat4 viewProj = m_Camera->getViewProjection();

		entt::basic_view meshes = m_Registry.view<MeshComponent>();

		for (entt::entity e : meshes)
		{	
			m_World->stepSimulation(ts);
			Entity entity = { e, this };
			auto name = entity.getName();
			MeshComponent& mesh = entity.getComponent<MeshComponent>();
			RigidBodyComponent& body = entity.getComponent<RigidBodyComponent>();

			if (name == "Cube1")
			{
				ImGui::SliderFloat3("Mesh position", &(float)body.pos.getX(), -10.0f, 10.0f);
				btTransform t;
				body.rigidBody->getMotionState()->getWorldTransform(t);
				m_World->debugDrawObject(t, body.shape, btVector3(255, 255, 255));
				// body.printPosition();
			}

			glm::mat4 modelTransform = body.getModelTransform();
			mesh.updateOrientation(modelTransform, viewProj);

			// m_World->debugDrawWorld();
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

	/**
	 * @brief Get an entity from the scene
	 * @param uuid is the uuid of the entity
	 * @return the entity if found, else { }
	*/
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