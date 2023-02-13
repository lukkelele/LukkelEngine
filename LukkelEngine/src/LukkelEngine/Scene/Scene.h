#pragma once

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Renderer/Camera.h"

#include <deque> // Temporary fix for unordered map has bug

#include "entt/entt.hpp"

namespace LukkelEngine {

	class Scene
	{
	public:
		Scene();
		~Scene();

		void onUpdate();
		bool isRunning() const { return m_IsRunning; }
		void pause(bool paused) { m_IsPaused = paused; }
		void tick(unsigned int frames = 1);

		void addEntity(Entity &entity);
		std::deque<Entity*>& getEntities() { return m_Entities; }

		Camera& getCamera() { return *m_Camera; }
		void updateCameraPosition(glm::vec3& newPosition);

		u_ptr<Camera> m_Camera;

	private:
		entt::registry m_Registry;
		std::deque<Entity*> m_Entities;

		bool m_IsRunning = false;
		bool m_IsPaused = false;
		int m_Frames = 0;

		s_ptr<Renderer> m_Renderer;
	};
}