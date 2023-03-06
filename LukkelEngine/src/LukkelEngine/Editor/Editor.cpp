#include "LKpch.h"
#include "LukkelEngine/Editor/Editor.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Physics/World.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


namespace LukkelEngine {

	Editor::Editor(s_ptr<Scene> scene)
		: m_Scene(scene)
	{
	}

	void Editor::createWorldObject(unsigned int objectType, std::string_view objectName)
	{

	}

	void Editor::addObject(WorldObject& worldObject)
	{

	}

	void selectEntity(Entity& entity)
	{

	}

}