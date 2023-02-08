#include <LukkelEngine/Core/Application.h>

namespace LukkelEngine {

	Application::Application()
	{
		LukkeLog::Log::init("LukkelEngine.log", "App", "Client");
		LKLOG_CRITICAL("Starting application");
		m_Window = Window::create();

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(m_Window->getWindow(), true);
		ImGui::StyleColorsDark();
		m_ImGuiInitialized = true;

		registerTests();

		/* Layer stack testing */
		Layer layer1;
		m_LayerStack.pushLayer(&layer1);
	}

	Application::~Application()
	{
		LKLOG_CRITICAL("Terminating application");
	}

	void Application::run(bool test)
	{
		// LKLOG_INFO("App->run()");
		// LKLOG_INFO("Testing: {0}", test);
		while (!glfwWindowShouldClose(m_Window->getWindow())) // while m_Running 
		{
			m_Renderer->clear();
			testRunner();
			{
				for (Layer* layer : m_LayerStack)
					layer->onUpdate(1.0f);
			}
			m_Window->onUpdate();
		}
	}

	void Application::testRunner()
	{
		if (currentTest) {
			ImGui_ImplGlfwGL3_NewFrame();
			currentTest->onUpdate(0.0f);
			currentTest->onRender();
			ImGui::Begin("Test");
			// Check if current test isn't test menu and back button clicked 
			if (currentTest != testMenu && ImGui::Button("<-"))
			{	// Delete current test and go back to test menu
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->onImGuiRender();
			ImGui::End();
		}
		m_Renderer->drawImGui();
	}

	void Application::registerTests()
	{
		testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
		testMenu->registerTest<test::TestClearColor>("Clear Color");
		testMenu->registerTest<test::TestTexture2D>("2D Texture");
		testMenu->registerTest<test::TestDrawTriangle>("Draw 2D triangle");
		testMenu->registerTest<test::TestDrawTriangle2>("Draw 2D triangle v2");
		testMenu->registerTest<test::TestDrawCube>("Draw 3D cube");
		testMenu->registerTest<test::TestShader>("Shader test");
		testMenu->registerTest<test::TestTexture>("Texture testing");
		testMenu->registerTest<test::TestKeyInput>("Key input");

	}

	void Application::pushLayer(Layer* layer)
	{
		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::popLayer(Layer* layer)
	{
		m_LayerStack.popLayer(layer);
		layer->onDetach();
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		// LKLOG_WARN("Event: WindowCloseEvent -> onWindowClose");
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
		// LKLOG_WARN("Event: WindowResizeEvent -> onWindowResize");
		// resizeWindow(e.getWidth(), e.getHeight());
		// LKLOG_TRACE("New window size is ({0}x{1})", e.getWidth(), e.getHeight());
		glViewport(0, 0, e.getWidth(), e.getHeight());
		return false;
	}

	void Application::onEvent(Event& e)
	{
		// LKLOG_WARN("[!] Event trigger: ", e);
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
