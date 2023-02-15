#include "LukkelEngine/Scene/Scene.h"


namespace LukkelEngine {

	Scene::Scene()
	{
		std::deque<Entity*> m_Entities;
		m_Camera = create_s_ptr<Camera>(-1.6f, 1.6f, -0.9f, 0.9f);
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
			entity->m_Shader->bind();
			/* Get transform */
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 1.0f));
			entity->m_Shader->setUniformMat4f("u_Transform", transform);

			glm::vec3 up = { 0.0f, 1.0f, 0.0f }; // Rotate with this to rotate as if looking left/right
			glm::vec3 target = { 0.0f, 0.0f, 1.0f };

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));
			// Rotate axis
			model = glm::rotate(model, m_Camera->getRotation(), up); // last vector is UP

			entity->m_Shader->setUniformMat4f("model", model);
			entity->m_Shader->setUniform4f("u_Color", 1.0, 0.8f, 1.0f, 1.0f);
			entity->m_Shader->setUniformMat4f("u_ViewProjection", m_Camera->getViewProjectionMatrix());

			s_ptr<VertexArray> va = entity->getVertexArray();
			s_ptr<IndexBuffer> ib = entity->getIndexBuffer();
			s_ptr<Shader> shader = entity->getVertexShader();
			// m_Renderer->draw(*va, *ib, *shader);
			m_Renderer->drawLines(*va, *ib, *shader);
		}
	}

	void Scene::addEntity(Entity& entity)
	{
		m_Entities.push_back(&entity);
	}


}