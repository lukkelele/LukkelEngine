#ifndef _LUKKELENGINE_LAYER_H
#define _LUKKELENGINE_LAYER_H

#include <LukkelEngine/Core/Base.h>
#include <LukkelEngine/Event/Event.h>

namespace LukkelEngine {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(float ts) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		const std::string& getName() const { return m_Name; }
	protected:
		std::string m_Name ; // Remove in release
	};
}

#endif /* _LUKKELENGINE_LAYER_H */