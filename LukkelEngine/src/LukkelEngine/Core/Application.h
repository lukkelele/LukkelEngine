#pragma once
#include <LukkelEngine/Core/Base.h>
#include <LukkelEngine/Core/Window.h>
#include <LukkelEngine/Core/LayerStack.h>
#include <LukkelEngine/Event/Event.h>
#include <LukkelEngine/Event/ApplicationEvent.h>
#include <Platform/Windows/Windows_Window.h>

/* EVENTS */
#include <LukkelEngine/Event/ApplicationEvent.h>
#include <LukkelEngine/Event/KeyEvent.h>
#include <LukkelEngine/Event/MouseEvent.h>

/* I/O */
#include <LukkelEngine/Core/Window.h>
#include <LukkelEngine/Input/Keyboard.h>

/* RENDERER */
#include <LukkelEngine/Renderer/Renderer.h>

/* TESTS */
#include <LukkelEngine/Test/Test.h>			
#include <LukkelEngine/Test/TestClearColor.h>
#include <LukkelEngine/Test/TestTexture2D.h>
#include <LukkelEngine/Test/TestDrawTriangle.h>
#include <LukkelEngine/Test/TestDrawTriangle2.h>
#include <LukkelEngine/Test/TestDrawCube.h>
#include <LukkelEngine/Test/TestShader.h>
#include <LukkelEngine/Test/TestTexture.h>
#include <LukkelEngine/Test/TestKeyInput.h>


namespace LukkelEngine {

	struct ApplicationDetails
	{
		std::string name = "LukkelEngine - Dev - Application";
		std::string directory;
	};

	class Application
	{
	private:
		ApplicationDetails details;
		static Application* s_Instance;

		bool m_Running = false;
		bool m_Minimized = false;
		bool m_ImGuiInitialized = false;

		Window* m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<Keyboard> m_Keyboard;
		LayerStack m_LayerStack;

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu;

		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);
		void resizeWindow(uint16_t width, uint16_t height);

		void testRunner();
		void registerTests();
		// void renderImGuiData();

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		void onEvent(Event& e);

	public:
		Application();
		~Application();

		void run(bool test = LK_DEBUG);
		void shutdown();
		void tick(uint8_t = 1);


	};
}