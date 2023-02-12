#include "LukkelEngine/Scene/Scene.h"


namespace LukkelEngine {

	Scene::Scene()
	{
		std::deque<Entity*> m_Entities;
		m_Camera = create_s_ptr<Camera>();
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

	// void Scene::addEntity(s_ptr<Entity> &entity)
	void Scene::addEntity(Entity& entity)
	{
		m_Entities.push_back(&entity);
	}


}