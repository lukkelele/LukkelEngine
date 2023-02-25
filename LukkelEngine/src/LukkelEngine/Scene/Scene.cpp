#include "LKpch.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Scene/Entity.h"

#include "glm/glm.hpp"


namespace LukkelEngine {

	Scene::Scene()
	{
		m_Camera = create_s_ptr<FpsCamera>(55.0f, 0.010f, 1000.0f);
		m_Camera->setPosition(glm::vec3(0.0f, 2.5f, -10.0f));
		// Create dynamic world for physics
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
		LKLOG_INFO("Scene entities: {0}", m_Registry.capacity());
		m_Camera->onUpdate(ts);
		// m_World->stepSimulation(ts);
		glm::mat4 viewProj = m_Camera->getViewProjection();

		entt::basic_view rigidBodies = m_Registry.view<RigidBody3DComponent>();
		entt::basic_view meshes = m_Registry.view<MeshComponent>();
		// Iterate through the available 3D bodies
		// for (entt::entity e : rigidBodies )
		for (entt::entity e : meshes)
		{	
			Entity entity = { e, this };
			LKLOG_WARN("3D Body: {0}", entity.getName());

			// Fetch components from current entity
			// RigidBody3DComponent& body3D = entity.getComponent<RigidBody3DComponent>();
			MeshComponent& mesh = entity.getComponent<MeshComponent>();
			// LKLOG_INFO("Fetched entity body and mesh components");
			// LKLOG_INFO("Getting 3D body model transform");
			// glm::mat4 modelTransform = body3D.getModelTransform();
			glm::mat4 modelTransform(1.0f);
			mesh.updateOrientation(modelTransform, viewProj);

			LKLOG_TRACE("va == nullptr : {0}", mesh.va == nullptr);
			LKLOG_TRACE("vb == nullptr : {0}", mesh.vb == nullptr);
			LKLOG_TRACE("ib == nullptr : {0}", mesh.ib == nullptr);
			LKLOG_TRACE("shader == nullptr : {0}", mesh.shader == nullptr);

			LKLOG_ERROR("Drawing mesh component");
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
		m_World->setGravity(LK_WORLD_GRAVITY_SLOWEST);
	}



}