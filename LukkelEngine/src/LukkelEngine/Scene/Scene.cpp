#include "LKpch.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Model/WorldObject.h"
#include "LukkelEngine/Debug/PhysicsDebugger.h"

#include "glm/glm.hpp"


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

	WorldObject Scene::createObject(const std::string& name)
	{
		WorldObject worldObject = createObjectWithUUID(UUID(), name);
		return worldObject;
	}

	WorldObject Scene::createObjectWithUUID(UUID uuid, const std::string& name)
	{
		WorldObject worldObject = { m_Registry.create(), this };
		worldObject.addComponent<IDComponent>(uuid);
		TagComponent& tag = worldObject.addComponent<TagComponent>();
		tag.tag = name.empty() ? "Object" : name;
		m_ObjectMap[uuid] = worldObject;
		return worldObject;
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

		auto worldObjects = m_Registry.view<WorldObject>();
		for (auto wo : worldObjects)
		{	
			WorldObject worldObject = { wo, this };
			worldObject.onUpdate(ts, viewProj);

			// m_Renderer->drawShape(mesh, btVector3(1, 1, 1));
			// m_Renderer->draw(mesh);
		}
	}

	void Scene::onImGuiRender()
	{
		m_Camera->onImGuiRender();
	}

	template<typename T>
		void Scene::onComponentAdded(WorldObject entity, T& component)
		{
			// static assert	
		}



}