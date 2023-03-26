#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Event/Event.h"

#include <imgui/imgui.h>


namespace LukkelEngine {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_Name; }

	protected:
		std::string m_Name;
	};
}
