#include "LukkelEngine/Scene/Scene.h"


namespace LukkelEngine {

	Scene::Scene()
	{
		std::deque<Entity*> m_Entities;
		m_Camera = create_u_ptr<Camera>(-1.6f, 1.6f, -0.9f, 0.9f);
	}
	
	Scene::~Scene()
	{
		for (auto& entity : m_Entities)
		{
			delete entity;
			LKLOG_WARN("Deleting entity");
		}
	}

	void Scene::onUpdate()
	{
		for (auto &entity : m_Entities) {
			s_ptr<VertexArray> va = entity->getVertexArray();
			auto ib = entity->getIndexBuffer();
			s_ptr<Shader> shader = entity->getVertexShader();
			m_Renderer->draw(*va, *ib, *shader);
		}
	}

	void Scene::addEntity(Entity& entity)
	{
		m_Entities.push_back(&entity);
	}

	/* This is needed because the references was weird when accessing camera directly */
	void Scene::updateCameraPosition(glm::vec3& newPosition)
	{
		m_Camera->setPosition(newPosition);
	}

}