#include <LukkelEngine/Core/Application.h>

namespace LukkelEngine {

	Application::Application(const ApplicationDetails& details)
	{
		LukkeLog::Log::init("LukkelEngine.log", "App", "Client");
		LKLOG_BLUE("Starting application");
		/* FIXME */
		WindowProps properties = WindowProps("Debug", 1600, 1024);
		m_Window = Window::create(properties);

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(m_Window->getWindow(), true);
		ImGui::StyleColorsDark();
		m_ImGuiInitialized = true;

		registerTests();
	}

	Application::~Application()
	{
		LKLOG_ERROR("Terminating application");
	}

	void Application::run(bool test)
	{
		while (!glfwWindowShouldClose(m_Window->getWindow())) // while m_Running 
		{
			onUpdate();
		}
	}

	void Application::onUpdate()
	{
		m_Renderer->clear();
		ImGui_ImplGlfwGL3_NewFrame();
		testRunner();

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			Layer* currentLayer = *it;
			currentLayer->onUpdate(1);
		}

		m_Renderer->drawImGui(); // RENDER IMGUI***

		m_Window->onUpdate();
	}

	void Application::testRunner()
	{
		if (currentTest) {
			// ImGui_ImplGlfwGL3_NewFrame();
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
		// m_Renderer->drawImGui();
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
