#pragma once 

#include "LukkelEngine/Core/Application.h" // Fix include dir in premake5 script

#include "LukkelEngine/Test/Test.h" // FIXME


namespace LukkelEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void begin();
		void end();
		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onUpdate(float ts) override;
		virtual void onImGuiRender() override;
		void onEvent(LukkelEngine::Event& e) override;

		void renderTestMenu();
		void registerTests();

	private:
		char m_Buffer[40 * 8] = { 0 }; // 40 Char buff, for input text

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu;
	};

}