#include "LKpch.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	Scene::Scene()
	{
		std::deque<Entity*> m_Entities;
		m_Camera = create_s_ptr<FpsCamera>(55.0f, 0.010f, 1000.0f);
		m_Camera->setPosition(glm::vec3(0.0f, 2.5f, -10.0f));
		// Create dynamic world for physics
		createDynamicWorld();

	}
	
	Scene::~Scene()
	{
		delete m_World;
	}

	void Scene::onUpdate(float ts)
	{
		m_Camera->onUpdate(ts);
		m_World->stepSimulation(ts);
		glm::mat4 viewProj = m_Camera->getViewProjection();

		for (auto &entity : m_Entities)
		{
			// auto body = entity->m_Body->getRigidBody();
			// btVector3 massPos = body->getCenterOfMassPosition();
			// float x = massPos.getX(), y = massPos.getY(), z = massPos.getZ();
			// entity->updateOrientation(viewProj);
			// s_ptr<VertexArray> va = entity->getVertexArray();
			// s_ptr<IndexBuffer> ib = entity->getIndexBuffer();
			// s_ptr<Shader> shader = entity->getShader();

			// LKLOG_INFO("Mass pos: ({0}, {1}, {2})", massPos.getX(), massPos.getY(), massPos.getZ());
			// m_Renderer->draw(*va, *ib, *shader);
		}
	}

	void Scene::onImGuiRender()
	{
		// auto entity = m_Entities.front();
		// auto body = entity->m_Body->getRigidBody();
		// btVector3 pos(entity->m_Position.x, entity->m_Position.y, entity->m_Position.z);

		// ImGui::Begin;
		// ImGui::SliderFloat3("Entity position", &entity->m_Position.x, -15.0f, 15.0f);
		// btTransform t;
		// body->getMotionState()->getWorldTransform(t);
		// btMatrix3x3 mat3(btQuaternion(0, 0, 0, 1));
		// body->setWorldTransform(btTransform(mat3, pos));
		// ImGui::End;

		// for (auto &entity : m_Entities)
		// {
		// }

	}
	Entity Scene::createEntity(const std::string entityName)
	{
		Entity entity = { m_Registry.create(), this };
		entity.Add
	}

	void Scene::addEntity(Entity& entity)
	{
		m_Entities.push_back(&entity);
		// m_World->addRigidBody(entity.getRigidBody());
	}

	void Scene::addCollider(btRigidBody* collisionBody)
	{
		m_World->addRigidBody(collisionBody);
	}

	/**
	 * @brief Create new dynamic world
	*/
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