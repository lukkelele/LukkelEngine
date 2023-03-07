#include "LKpch.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Physics/World.h"
#include "LukkelEngine/Debug/PhysicsDebugger.h"


namespace LukkelEngine {

	Scene::Scene()
	{
		m_Camera = create_s_ptr<FpsCamera>(45.0f, 0.010f, 1000.0f);
		m_Camera->setPosition(glm::vec3(0.0f, 15.0f, -46.0f));
		m_Camera->setScene(this);

		m_World = create_s_ptr<World>();
		m_World->initPhysics(this);
	}
	
	Scene::~Scene()
	{
	}

	Entity Scene::createEntity(const std::string& name)
	{
		Entity entity = createEntityWithUUID(UUID(), name);
		return entity;
	}

	Entity Scene::createEntityWithUUID(UUID uuid, const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.addComponent<IDComponent>(uuid);
		TagComponent& tag = entity.addComponent<TagComponent>();
		tag.tag = name.empty() ? "Entity" : name;
		m_EntityMap[uuid] = entity;
		return entity;
	}

	Entity Scene::getEntityWithUUID(UUID uuid)
	{
		if (m_EntityMap.find(uuid) != m_EntityMap.end())
			return { m_EntityMap.at(uuid), this };
		return { };
	}

	Entity Scene::findEntity(std::string_view name)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto entity : view)
		{
			const TagComponent& tc = view.get<TagComponent>(entity);
			if (tc.tag == name)
				return Entity{ entity , this };
		}
		return {};
	}

	void Scene::destroyEntity(Entity entity)
	{
		m_EntityMap.erase(entity.getUUID());
		m_Registry.destroy(entity);
		LKLOG_CRITICAL("Entity successfully deleted");
	}

	void Scene::onUpdate(float ts)
	{
		m_Camera->onUpdate(ts);
		m_World->onUpdate(ts);

		// If mouse has moved -> send World Mouse move event
		if (m_Camera->hasMouseMoved)
		{
			m_World->mouseMoveCallback(Mouse::getMouseX(), Mouse::getMouseY());
		}

		glm::mat4 viewProj = m_Camera->getViewProjection();

		if (Mouse::isButtonPressed(MouseButton::Button0))
			m_World->mouseButtonCallback(MouseButton::Button0, 1, Mouse::getMouseX(), Mouse::getMouseY());

		auto entities = m_Registry.view<Entity>();
		LKLOG_INFO("entities: {0}", entities.size());

		// for (auto ent : entities)
		for (auto ent : m_Entities)
		{	
			Entity entity = { ent, this };
			LKLOG_TRACE("-> {0}", entity.getName());
			entity.onUpdate(ts, viewProj);
			m_Renderer->drawShape(entity);
			// m_Renderer->draw(mesh);
		}
	}

	void Scene::onImGuiRender()
	{
		m_Camera->onImGuiRender();
	}

	template<typename T>
		void Scene::onComponentAdded(Entity entity, T& component)
		{
			// static assert	
		}


}