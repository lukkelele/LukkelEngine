#pragma once
#include "entt/entt.hpp"
#include "LukkelEngine/Scene/Scene.h"

namespace LukkelEngine {

	class Entity
	{
	private:
		entt::entity m_EntityHandle{ entt::null };

	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& otherEntity) = default;

		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator bool() const { return m_EntityHandle != entt::null; }

	};

}