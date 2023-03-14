#pragma once
#include "LukkelEngine/Core/Layer.h"


namespace LukkelEngine {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer() = default;

		void onImGuiRender();
		void onUpdate();

	private:
	};

}