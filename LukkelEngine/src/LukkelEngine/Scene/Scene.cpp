#include "LukkelEngine/Scene/Scene.h"


namespace LukkelEngine {

	Scene::Scene()
	{
		std::deque<Entity*> m_Entities;
		m_Camera = create_s_ptr<FpsCamera>(50.0f, 0.10f, 1000.0f);
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

			// Get translation for the object
			glm::vec3 translation = entity->m_Translation;
			ImGui::SliderFloat("Entity translation", &translation.x , -200.0f, 400.0f);

			// Camera position
			glm::vec3 pos = m_Camera->getPosition();
			ImGui::SliderFloat3("Camera pos", &m_Camera->m_Position.x, -50, 50);
			ImGui::SliderFloat("Camera rotation speed", &(m_Camera->m_RotationSpeed), 0.01f, 4.0f);
			LKLOG_CLIENT_INFO("Atilla CLIENT");
			LKLOG_CLIENT_TRACE("Atilla CLIENT");
			LKLOG_WARN("ATILLA ATILLA");
			LKLOG_ERROR("ATILLA ATILLA {0} {1}", 5.0f, 2);
			LKLOG_CRITICAL("ATILLA ATILLA {0} {1}", 5.0f, 2);

			glm::mat4 model = glm::mat4(1.0f);
			// model = glm::translate(model, translation);
			model = glm::translate(model, m_Camera->m_Position);
			// Rotate axis
			model = glm::rotate(model, m_Camera->getRotation(), up); // last vector is UP

			entity->m_Shader->setUniformMat4f("model", model);
			entity->m_Shader->setUniformMat4f("u_ViewProjection", m_Camera->getViewProjectionMatrix());

			s_ptr<VertexArray> va = entity->getVertexArray();
			s_ptr<IndexBuffer> ib = entity->getIndexBuffer();
			s_ptr<Shader> shader = entity->getVertexShader();

			m_Renderer->drawLines(*va, *ib, *shader);
			//m_Renderer->draw(*va, *ib, *shader);
		}
	}

	void Scene::addEntity(Entity& entity)
	{
		m_Entities.push_back(&entity);
	}


}