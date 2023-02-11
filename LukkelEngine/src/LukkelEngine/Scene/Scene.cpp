#include "LukkelEngine/Scene/Scene.h"

namespace LukkelEngine {

	Scene::Scene()
	{
		std::deque<Entity*> m_Entities;
	}
	
	Scene::~Scene()
	{
	}

	void Scene::onUpdate()
	{
		// LKLOG_TRACE("Scene->onUpdate()");
		for (auto &entity : m_Entities) {
			s_ptr<VertexArray> va = entity->getVertexArray();
			LKLOG_TRACE("Va RenderID: {0}", va->m_RendererID);
			auto ib = entity->getIndexBuffer();
			s_ptr<Shader> shader = entity->getVertexShader();
			LKLOG_WARN("Renderer->draw()");
			m_Renderer->draw(*va, *ib, *shader);
		}

	}

	void Scene::addEntity(s_ptr<Entity> entity)
	{
		m_Entities.push_back(entity);
		LKLOG_WARN("Added entity! => m_Entities size: {0}", m_Entities.size());
	}


}