#ifdef LK_USE_PRECOMPILED_HEADERS
	#include <LKpch.h>
#endif
#include <LukkelEngine/LukkelEngine.h>

namespace LukkelEngine {

	LukkelEngine::LukkelEngine()
	{
		m_Blending = LK_DEFAULT_BLENDING_MODE;
		m_GraphicsMode = LK_GRAPHICS_MODE_3D;
	}

	LukkelEngine::~LukkelEngine()
	{
		// TERMINATE ALL 
		LK_CORE_WARN("Terminating LukkelEngine");
		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
		// Move this to terminate ImGui and opengl inside Window
		ImGui_ImplGlfwGL3_Shutdown(); // FIXME
		ImGui::DestroyContext();
		glfwTerminate();
	}

	void LukkelEngine::init(uint8_t graphicsMode, bool blending)
	{
		/* Enable logging */
		m_Running = true;
		Log::init();
		LK_CORE_WARN("Starting LukkelEngine");

		LK_CORE_TRACE("Creating window ({0}x{1})", DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
		m_Window = std::unique_ptr<Window>(Window::create());
		initImGui();

		// Initiate I/O
		LK_CORE_WARN("Attaching I/O modules...");
		m_Keyboard->bind(m_Window->getWindow());
		// GLCall(glfwSetKeyCallback(m_Window, m_Keyboard.));
		
		// Test registration
		LK_CORE_WARN("Registering tests...");
		registerTests();

		setBlending(blending);
	}

	GLFWwindow* LukkelEngine::getWindow() { return m_Window->getWindow(); }

	void LukkelEngine::registerTests()
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

	void LukkelEngine::screenUpdate()
	{
		m_Renderer->clear();
	}

	void LukkelEngine::initImGui()
	{
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(m_Window->getWindow(), true);
		ImGui::StyleColorsDark();
		m_ImGuiInitialized = true;
	}

	void LukkelEngine::renderImGuiData()
	{
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void LukkelEngine::render()
	{
		renderImGuiData();
		m_Window->onUpdate();
	}

	void LukkelEngine::setMode(unsigned int setting)
	{
		m_GraphicsMode = setting;
		if (m_GraphicsMode == LK_GRAPHICS_MODE_3D)  // 1
			GLCall(glEnable(GL_DEPTH_TEST));
		if (m_GraphicsMode == LK_GRAPHICS_MODE_2D)	// 0
			GLCall(glDisable(GL_DEPTH_TEST));
	}

	void LukkelEngine::setBlending(unsigned int setting)
	{
		m_Blending = setting;
		if (m_Blending > 1)
			m_Blending = LK_DEFAULT_BLENDING_MODE;
		if (m_Blending == LK_BLENDING_ENABLED) {
			LK_CORE_TRACE("Enabling blending");
			GLCall(glEnable(GL_BLEND));
			GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		} else {
			LK_CORE_TRACE("Disabling blending");
			GLCall(glDisable(GL_BLEND));
		}
	}

	void LukkelEngine::testRunner(float updateFrequency)
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
	}

	void LukkelEngine::pushLayer(Layer* layer)
	{
		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void LukkelEngine::popLayer(Layer* layer)
	{
		m_LayerStack.popLayer(layer);
		layer->onDetach();
	}

	bool LukkelEngine::onWindowClose(WindowCloseEvent& e)
	{
		LK_CORE_WARN("Event: WindowCloseEvent -> onWindowClose");
		m_Running = false;
		return true;
	}

	bool LukkelEngine::onWindowResize(WindowResizeEvent& e)
	{
		if (e.getWidth() == 0 || e.getHeight() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		LK_CORE_WARN("Event: WindowResizeEvent -> onWindowResize");
		// resizeWindow(e.getWidth(), e.getHeight());
		LK_CORE_TRACE("New window size is ({0}x{1})", e.getWidth(), e.getHeight());
		glViewport(0, 0, e.getWidth(), e.getHeight());
		// m_Renderer->onWindowResize(e.getWidth(), e.getHeight());
		return false;
	}

	void LukkelEngine::onEvent(Event& e)
	{
		LK_CORE_WARN("[!] Event trigger: ", e);
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


	void LukkelEngine::resizeWindow(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}

}
