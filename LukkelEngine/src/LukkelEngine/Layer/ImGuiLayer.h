#pragma once 

#include "LukkelEngine/Core/Application.h" // Fix include dir in premake5 script



namespace LukkelEngine {

	class ImGuiLayer : public Layer
	{
		ImGuiLayer();
		~ImGuiLayer() = default;

		void begin();
		void end();
		virtual void onAttach() override;
		virtual void onDetach() override;
		void onUpdate() override;
		virtual void onImGuiRender() override;
		void onEvent(LukkelEngine::Event& e) override;

	private:
		LukkelEngine::s_ptr<LukkelEngine::Scene> m_Scene;
	};

}