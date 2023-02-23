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
		glm::mat4 viewProj = m_Camera->getViewProjection();
		for (auto &entity : m_Entities)
		{
			entity->updateOrientation(viewProj);
			s_ptr<VertexArray> va = entity->getVertexArray();
			s_ptr<IndexBuffer> ib = entity->getIndexBuffer();
			s_ptr<Shader> shader = entity->getShader();

			m_Renderer->draw(*va, *ib, *shader);
		}
		m_WorldPhysics->m_DynamicWorld->stepSimulation(0.0035f);
	}

	void Scene::onImGuiRender()
	{
	}

	void Scene::addEntity(Entity& entity)
	{
		m_Entities.push_back(&entity);
	}


}