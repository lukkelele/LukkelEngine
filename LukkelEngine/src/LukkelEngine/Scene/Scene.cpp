#include "LukkelEngine/Scene/Scene.h"

#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	Scene::Scene()
	{
		std::deque<Entity*> m_Entities;
		m_Camera = create_s_ptr<FpsCamera>(45.0f, 0.010f, 1000.0f);
		m_Camera->setPosition(glm::vec3(0.0f, 2.5f, -10.0f));
		// Create dynamic world for physics
		createDynamicWorld();

		// HARDCODED GROUND OBJECT
		btVector3 groundPosition(0.0f, -2.0f, 0.0f);

		// if (m_World->getDebugDrawer())
		//		m_World->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe + btIDebugDraw::DBG_DrawContactPoints);

		btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
		btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1.0f, 0)));
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f, new btDefaultMotionState(), groundShape, groundPosition);
		btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
		groundRigidBody->setFriction(0.5f);
		groundRigidBody->setRestitution(0.9f);
		groundRigidBody->setCustomDebugColor(btVector3(100, 100, 100));
		m_World->addRigidBody(groundRigidBody);
	}
	
	Scene::~Scene()
	{
		for (auto& entity : m_Entities)
		{
			LKLOG_WARN("Deleting entity...");
			delete entity;
		}
	}

	void Scene::onUpdate(float ts)
	{
		m_Camera->onUpdate(ts);
		m_World->stepSimulation(ts);
		glm::mat4 viewProj = m_Camera->getViewProjection();

		for (auto &entity : m_Entities)
		{
			entity->updateOrientation(viewProj);
			s_ptr<VertexArray> va = entity->getVertexArray();
			s_ptr<IndexBuffer> ib = entity->getIndexBuffer();
			s_ptr<Shader> shader = entity->getShader();

			m_Renderer->draw(*va, *ib, *shader);
		}
	}

	void Scene::onImGuiRender()
	{
	}

	void Scene::addEntity(Entity& entity)
	{
		m_Entities.push_back(&entity);
		m_World->addRigidBody(entity.getRigidBody());
		// m_World->addRigidBody(entity.m_Body->m_RigidBody);
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
		// Gravity set to -9.8 m^2/2
		m_World->setGravity(LK_WORLD_GRAVITY_SLOWEST);
	}



}