#include "LukkelEngine/Scene/Scene.h"

#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	Scene::Scene()
	{
		std::deque<Entity*> m_Entities;
		m_Camera = create_s_ptr<FpsCamera>(50.0f, 0.010f, 1000.0f);
		// Create world physics
		m_WorldPhysics = new WorldPhysics(LK_WORLD_DYNAMIC); // Dynamic World
	}
	
	Scene::~Scene()
	{
		for (auto& entity : m_Entities)
		{
			LKLOG_WARN("Deleting entity");
			delete entity;
		}
	}

	void Scene::onUpdate(float ts)
	{
		m_Camera->onUpdate(ts);

		for (auto &entity : m_Entities)
		{
			entity->m_Texture->bind();
			entity->m_Shader->bind();

			btTransform t;
			entity->m_RigidBody->getMotionState()->getWorldTransform(t);
			btVector3 translate = t.getOrigin();
			float x = translate.getX();
			float y = translate.getY();
			float z = translate.getZ();

			LKLOG_CLIENT_WARN("RigidBody -> ({0}, {1}, {2})", x, y, z);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
			entity->m_Shader->setUniformMat4f("u_Transform", transform);

			m_WorldPhysics->m_DynamicWorld->stepSimulation(0.0035f);

			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

			auto entityShader = entity->getShader();
			entityShader->setUniformMat4f("model", model);
			entityShader->setUniformMat4f("u_ViewProjection", m_Camera->getViewProjectionMatrix());

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
	}


}