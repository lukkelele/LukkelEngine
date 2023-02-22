#pragma once

#include <deque> // Temporary fix because unordered map bugs out

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Renderer/FpsCamera.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Physics/WorldPhysics.h"

#include "entt/entt.hpp"

namespace LukkelEngine {

	class Scene
	{
	public:
		Scene();
		~Scene();

		void onUpdate(float ts);
		void onImGuiRender();

		bool isRunning() const { return m_IsRunning; }
		void pause(bool paused) { m_IsPaused = paused; }

		void addEntity(Entity &entity);
		std::deque<Entity*>& getEntities() { return m_Entities; }
		const s_ptr<FpsCamera> getCamera() const { return m_Camera; }

		WorldPhysics* m_WorldPhysics;

	private:
		bool m_IsRunning = false, m_IsPaused = false;
		int m_Frames = 0;

		entt::registry m_Registry;
		std::deque<Entity*> m_Entities;
		s_ptr<Renderer> m_Renderer;
		s_ptr<FpsCamera> m_Camera;

		// Physics
		// u_ptr<WorldPhysics> m_WorldPhysics;
	};
}