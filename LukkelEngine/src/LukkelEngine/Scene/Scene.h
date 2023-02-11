#pragma once

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Scene/Entity.h"
#include <deque> // Temporary fix for unordered map has bug

#include "entt/entt.hpp"

namespace LukkelEngine {

	class Scene
	{
	public:
		Scene();
		~Scene();

		/* Runtime */
		void onUpdate();
		bool isRunning() const { return m_IsRunning; }
		void pause(bool paused) { m_IsPaused = paused; }
		void tick(unsigned int frames = 1);

		void addEntity(s_ptr<Entity> &entity);

	private:
		entt::registry m_Registry;
		// std::unordered_map<UUID, entt::entity> m_Entities;
		std::deque<s_ptr<Entity>> m_Entities;
		bool m_IsRunning = false;
		bool m_IsPaused = false;
		int m_Frames = 0;

		// Renderer m_Renderer;
		s_ptr<Renderer> m_Renderer;
	};
}