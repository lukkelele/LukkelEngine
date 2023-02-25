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
			RigidBody3DComponent& body3D = entity.getComponent<RigidBody3DComponent>();
			MeshComponent& mesh = entity.getComponent<MeshComponent>();

			glm::mat4 modelTransform = body3D.getModelTransform();
			mesh.updateOrientation(modelTransform, viewProj);
			body3D.printPosition();

			m_Renderer->draw(*mesh.va, *mesh.ib, *mesh.shader);
		}
	}

	void Scene::onImGuiRender()
	{
		ImGui::Begin;
		auto entity = findEntity("Test Cube");
		auto mesh = entity.getComponent<MeshComponent>();
		ImGui::SliderFloat3("Entity position", &mesh.pos.x, -15.0f, 15.0f);
		auto bc = entity.getComponent<RigidBody3DComponent>();
		btVector3 pos(mesh.pos.x, mesh.pos.y, mesh.pos.z);

		btTransform t;
		bc.rigidBody->getMotionState()->getWorldTransform(t);
		btMatrix3x3 mat3(btQuaternion(0, 0, 0, 1));
		bc.rigidBody->setWorldTransform(btTransform(mat3, pos));
		ImGui::End;
		LKLOG_INFO("[UPDATE] Entity pos: ({0}, {1}, {2})", mesh.pos.x, mesh.pos.y, mesh.pos.z);
	}

	void Scene::createDynamicWorld()
	{
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();
		btDefaultCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

		m_World = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
		m_World->setGravity(LK_WORLD_GRAVITY_DEFAULT);
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

}