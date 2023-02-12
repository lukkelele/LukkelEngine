#pragma once

#include "GL/glew.h"
#include "glfw/glfw3.h"
#include "imgui/imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/Window.h"
#include "LukkelEngine/Core/LayerStack.h"
#include "LukkelEngine/Event/Event.h"
#include "LukkelEngine/Scene/Scene.h"
#include "Platform/Windows/Windows_Window.h"

/* EVENTS */
#include <LukkelEngine/Event/ApplicationEvent.h>
//#include <LukkelEngine/Event/KeyEvent.h>
//#include <LukkelEngine/Event/MouseEvent.h>

/* I/O */
#include <LukkelEngine/Core/Window.h>
#include <LukkelEngine/Input/Keyboard.h>
// #include <LukkelEngine/Input/Mouse.h>

#include "LukkelEngine/Layer/ImGuiLayer.h"

/* TESTS */
#include <LukkelEngine/Test/Test.h>			
#include <LukkelEngine/Test/TestClearColor.h>
#include <LukkelEngine/Test/TestTexture2D.h>
#include <LukkelEngine/Test/TestDrawTriangle.h>
#include <LukkelEngine/Test/TestDrawTriangle2.h>
#include <LukkelEngine/Test/TestDrawCube.h>
#include <LukkelEngine/Test/TestShader.h>
#include <LukkelEngine/Test/TestTexture.h>


namespace LukkelEngine {

	struct ApplicationDetails
	{
		std::string name = "LukkelEngine - Dev - Application";
		std::string directory;
	};

	class Application
	{
	public:
		Application(const ApplicationDetails& details = ApplicationDetails());
		~Application();

		void run(bool test = LK_DEBUG);
		void onUpdate(); // per tick
		void shutdown();

		/* Layer */
		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		/* Overlay */
		void pushOverlay(Layer* layer);
		void popOverlay(Layer* layer);

		void onEvent(Event& e);

		GLFWwindow* getWindow() { return m_Window->getWindow(); }
		int getViewportWidth() { return m_Window->getWidth(); }
		int getViewportHeight() { return m_Window->getWidth(); }

		// Used for getting current user window, cross platform
		static Application& get() { return *s_Instance; }

	protected:
		ApplicationDetails details;
		static Application* s_Instance;

		bool m_Running = false;
		bool m_Minimized = false;
		bool m_ImGuiInitialized = false;

		// TODO: Change to smart pointers
		// They are protected, so they should be inherited to Sandbox (?)
		// s_ptr<Window> m_Window;
		Window* m_Window;
		u_ptr<Renderer> m_Renderer;
		u_ptr<Keyboard> m_Keyboard;
		LayerStack m_LayerStack;

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu;

		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);
		void resizeWindow(uint16_t width, uint16_t height);

		void testRunner();
		void registerTests();

	};
}