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
		m_Entities.push_back(entity);
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
			auto name = entity.getName();
			LKLOG_TRACE("Entity NAME: {0}", name);
			// Sync the positions
			MeshComponent& mesh = entity.getComponent<MeshComponent>();
			RigidBody3DComponent& body = entity.getComponent<RigidBody3DComponent>();
			// mesh.pos.x = body.pos.getX();
			// mesh.pos.y = body.pos.getY();
			// mesh.pos.z = body.pos.getZ();
			// body.pos = btVector3(mesh.pos.x, mesh.pos.y, mesh.pos.z);

			if (name == "Cube1")
			{
				// ImGui::SliderFloat3("Mesh position", &(float)body.pos.getX(), -20.0f, 20.0f);
				ImGui::SliderFloat3("Mesh position", &mesh.pos.x, -15.0f, 15.0f);
				btTransform t;
				btMatrix3x3 mat3(btQuaternion(0, 0, 0, 1));
				body.rigidBody->getMotionState()->getWorldTransform(t);
				body.rigidBody->setWorldTransform(btTransform(mat3, btVector3(mesh.pos.x, mesh.pos.y, mesh.pos.z)));
				// body.rigidBody->setWorldTransform(btTransform(mat3, body.pos));
			}
			auto meshTranslation = mesh.getTranslation();
			glm::mat4 modelTransform = body.getModelTransform(meshTranslation);
			mesh.updateOrientation(modelTransform, viewProj);
			body.printPosition();

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