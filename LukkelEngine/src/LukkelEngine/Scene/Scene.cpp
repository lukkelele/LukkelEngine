#include "LukkelEngine/Scene/Scene.h"

#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	Scene::Scene()
	{
		std::deque<Entity*> m_Entities;
		m_Camera = create_s_ptr<FpsCamera>(50.0f, 0.010f, 1000.0f);
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
			/* Get transform */
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			entity->m_Shader->setUniformMat4f("u_Transform", transform);

			glm::vec3 up = { 0.0f, 1.0f, 0.0f }; // Rotate with this to rotate as if looking left/right

			// Get translation for the object
			glm::vec3 translation = entity->m_Translation;
			ImGui::SliderFloat("Entity translation", &translation.x , -200.0f, 400.0f);


			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, m_Camera->m_Position);
			// Rotate axis
			model = glm::rotate(model, m_Camera->getRotation(), m_Camera->getUpDirection()); // last vector is UP

			ImGui::SliderFloat3("Camera position", &m_Camera->m_Position.x, -40.0f, 40.0f);
			auto entityShader = entity->getShader();
			entityShader->setUniformMat4f("model", model);
			entityShader->setUniformMat4f("u_ViewProjection", m_Camera->getViewProjectionMatrix());

			s_ptr<VertexArray> va = entity->getVertexArray();
			s_ptr<IndexBuffer> ib = entity->getIndexBuffer();
			s_ptr<Shader> shader = entity->getShader();

			m_Renderer->drawLines(*va, *ib, *shader);
			// m_Renderer->draw(*va, *ib, *shader);
		}
	}

	void Scene::addEntity(Entity& entity)
	{
		m_Entities.push_back(&entity);
	}


}