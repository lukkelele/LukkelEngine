#include <LukkelEngine/Core/Application.h>

namespace LukkelEngine {

	Application* Application::s_Instance;
	bool Application::s_IsNewImGuiFrame = false;

	Application::Application(const ApplicationDetails& details)
	{
		s_Instance = this;
		// s_IsNewImGuiFrame = false;
		LukkeLog::Log::init("LukkelEngine.log", "App", "Client");
		LKLOG_TRACE("Starting application");
		WindowProps properties = WindowProps(details.title, details.width, details.height);
		m_Window = Window::create(properties);

		Layer* imguiLayer = new ImGuiLayer();
		pushOverlay(imguiLayer);
	}

	Application::~Application()
	{
		LKLOG_WARN("Terminating application");
	}

	void Application::run(bool test)
	{
		while (!glfwWindowShouldClose(m_Window->getWindow())) // while m_Running 
		{
			int state = glfwGetKey(m_Window->getWindow(), GLFW_KEY_W);
			onUpdate();
		}
	}

	void Application::onUpdate(float ts)
	{
		m_Renderer->clear();
		ImGui_ImplGlfwGL3_NewFrame();

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) 
		{
			Layer* currentLayer = *it;
			currentLayer->onUpdate(ts);
		}

		m_Renderer->drawImGui(); // ImGui Render
		m_Window->onUpdate();
	}
	/**
	 * Push a layer to the layer stack
	 * @param layer is the layer to be pushed
	*/
	void Application::pushLayer(Layer* layer)
	{
		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	/**
	 * Push an overlay to the layer stack
	 * @param layer is the layer to be pushed
	*/
	void Application::pushOverlay(Layer* layer)
	{
		m_LayerStack.pushOverlay(layer);
		layer->onAttach();
	}

	/**
	 * Pop a layer from the layer stack
	 * @param layer is the layer to be popped
	*/
	void Application::popLayer(Layer* layer)
	{
		m_LayerStack.popLayer(layer);
		layer->onDetach();
	}
	/**
	 * Pop an overlay from the layer stack
	 * @param layer is the layer to be popped
	*/
	void Application::popOverlay(Layer* layer)
	{
		m_LayerStack.popOverlay(layer);
		layer->onDetach();
	}


	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& e)
	{
		if (e.getWidth() == 0 || e.getHeight() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		glViewport(0, 0, e.getWidth(), e.getHeight());
		return false;
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher ed(e);
		ed.dispatch<WindowCloseEvent>(LK_BIND_EVENT_FN(onWindowClose));
		ed.dispatch<WindowResizeEvent>(LK_BIND_EVENT_FN(onWindowResize));
		/* Handle events */
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			if (e.handled)
				break;
			(*it)->onEvent(e);
		}
	}

	void Application::resizeWindow(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}


}
