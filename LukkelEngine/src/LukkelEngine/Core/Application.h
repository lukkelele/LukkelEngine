#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "LukkelEngine/UI/ImGuiLayer.h"

#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/Window.h"
#include "LukkelEngine/Core/LayerStack.h"
#include "LukkelEngine/Core/Timer.h"
#include "LukkelEngine/Core/TimeStep.h"

#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Event/Event.h"


namespace LukkelEngine {

	struct ApplicationDetails
	{
		std::string title;
		uint16_t width, height;
		std::string directory;
		ApplicationDetails(const std::string& title = "LukkelEngine - Application",
						   uint16_t width = 1600,
						   uint16_t height = 1240)
			: title(title), width(width), height(height){}
	};

	class Application
	{
	public:
		Application(const ApplicationDetails& details = ApplicationDetails());
		~Application();

		void run();
		void onUpdate(float ts = 1.0f);
		void shutdown();
		void onEvent(Event& e);

		GLFWwindow* getGLFWwindow() const { return m_Window->getWindow(); }
		s_ptr<Window> getWindow() const { return m_Window; }
		// s_ptr<FpsCamera> getCamera() const { return m_Scene->getCamera(); }
		s_ptr<Camera> getCamera() const { return m_Scene->getCamera(); }
		s_ptr<Scene> getScene() const { return m_Scene; }
		void setScene(s_ptr<Scene>& scene) { m_Scene = scene; }

		int getViewportWidth() { return m_Details.width; }
		int getViewportHeight() { return m_Details.height; }

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		void pushOverlay(Layer* layer);
		void popOverlay(Layer* layer);

		// bool onWindowClose(WindowCloseEvent& e);
		// bool onWindowResize(WindowResizeEvent& e);
		void resizeWindow(uint16_t width, uint16_t height);

		static Application& get() { return *s_Instance; }

	private:
		ApplicationDetails m_Details;
		static Application* s_Instance;
		
		bool m_Running = false;
		bool m_Minimized = false;
		float m_LastTime = 0.0f;

		s_ptr<Window> m_Window;
		u_ptr<Renderer> m_Renderer;
		u_ptr<Keyboard> m_Keyboard;
		s_ptr<Scene> m_Scene;
		LayerStack m_LayerStack;
		Timer m_Timer;
		ImGuiLayer* m_ImGuiLayer;
	};
}
