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

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			entity->m_Shader->setUniformMat4f("u_Transform", transform);

			// Get translation for the object
			glm::vec3 translation = entity->m_Translation;
			ImGui::SliderFloat("Entity translation", &translation.x , -200.0f, 400.0f);

			glm::mat4 model = glm::mat4(1.0f);
			auto entityShader = entity->getShader();
			entityShader->setUniformMat4f("model", model);
			entityShader->setUniformMat4f("u_ViewProjection", m_Camera->getViewProjectionMatrix());

			s_ptr<VertexArray> va = entity->getVertexArray();
			s_ptr<IndexBuffer> ib = entity->getIndexBuffer();
			s_ptr<Shader> shader = entity->getShader();

			m_Renderer->drawLines(*va, *ib, *shader);
			// m_Renderer->draw(*va, *ib, *shader);
		}
		onImGuiRender();
	}

	void Scene::onImGuiRender()
	{
		auto cam = getCamera();
		ImGui::SliderFloat("Camera speed", &cam->m_Speed, 0.010f, 2.0f);
		ImGui::SliderFloat("FOV", &cam->m_FOV, 25.0f, 120.0f);
		ImGui::Text("Average FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
		ImGui::SliderFloat3("Camera position", &m_Camera->m_Position.x, -40.0f, 40.0f);
		ImGui::Checkbox("Enable mouse", &getCamera()->m_MouseEnabled);
	}

	void Scene::addEntity(Entity& entity)
	{
		m_Entities.push_back(&entity);
	}


}