#pragma once
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Physics/RigidBody.h"
#include "LukkelEngine/Renderer/Material.h"
#include "LukkelEngine/UI/Property.h"
#include "LukkelEngine/UI/Widgets.h"

#include "entt/entt.hpp"

namespace LukkelEngine {

	enum LK_OBJECT
	{
		LINE, CUBE, SPHERE
	};

	class EditorLayer
	{
	public:
		EditorLayer(s_ptr<Scene> scene);
		~EditorLayer() = default;

		void OnImGuiRender();
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
		void SelectEntity(Entity& entity);

		template<typename T, typename UIFunction>
		static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction);

		template<typename T>
		void DisplayAddComponentEntry(const std::string& entryName);

	private:
		s_ptr<Scene> m_Scene = nullptr;
		static Entity m_SelectedEntity;

		// 7 equals 0b111, the gizmo types are set 1 for each axis at an offset of 3 bits
		enum GizmoType
		{
			TRANSLATE = 7 << 0,
			ROTATE	  = 7 << 3,
			SCALE     = 7 << 6
		};

		int m_GizmoType = GizmoType::TRANSLATE;

		friend class World;
	};

}