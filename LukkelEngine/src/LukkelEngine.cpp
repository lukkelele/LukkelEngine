#include <LukkelEngine.h>

namespace LukkelEngine {

	LukkelEngine::LukkelEngine()
	{
		status = init(DEFAULT_GRAPHICS_MODE, DEFAULT_BLENDING_MODE);
	}

	LukkelEngine::LukkelEngine(unsigned int graphicsMode)
	{
		status = init(graphicsMode, DEFAULT_BLENDING_MODE);
	}

	LukkelEngine::LukkelEngine(unsigned int graphicsMode, unsigned int blending)
	{
		status = init(graphicsMode, blending);
	}

	LukkelEngine::~LukkelEngine()
	{
		// TERMINATE ALL 
		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
		
		ImGui_ImplGlfwGL3_Shutdown(); // FIXME
		ImGui::DestroyContext();
		glfwTerminate();
	}

	GLFWwindow* LukkelEngine::getWindow() { return m_Window->getWindow(); }

	int LukkelEngine::init(unsigned int graphicsMode, unsigned int blending)
	{
		// Check for PLATFORM
		m_Window = std::unique_ptr<Window>(Window::create());
		//m_Window = initDisplay(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "LukkelEngine", 3, 3);

		// Initiate I/O
		LOG("Creating I/O modules...");
		Keyboard m_Keyboard;
		m_Keyboard.Bind(m_Window->getWindow());
		// GLCall(glfwSetKeyCallback(m_Window, m_Keyboard.));
		
		// Test registration
		registerTests();

		return 1;
	}

	int LukkelEngine::registerTests()
	{
		testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
		// Register tests
		testMenu->registerTest<test::TestClearColor>("Clear Color");
		testMenu->registerTest<test::TestTexture2D>("2D Texture");
		testMenu->registerTest<test::TestDrawTriangle>("Draw 2D triangle");
		testMenu->registerTest<test::TestDrawTriangle2>("Draw 2D triangle v2");
		testMenu->registerTest<test::TestDrawCube>("Draw 3D cube");
		testMenu->registerTest<test::TestShader>("Shader test");
		testMenu->registerTest<test::TestTexture>("Texture testing");
		testMenu->registerTest<test::TestKeyInput>("Key input");
		test::TestKeyInput* TestKeyInput_ptr = dynamic_cast<test::TestKeyInput*>(currentTest);
		// TestKeyInput_ptr->SetWindow(*window);
		LOG("Tests created!");
		return 1;
	}

	void LukkelEngine::screenUpdate()
	{
		m_Renderer.clear();
	}

	int LukkelEngine::initImGui()
	{
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(m_Window, true);
		ImGui::StyleColorsDark();
		return 1;
	}

	void LukkelEngine::renderImGuiData()
	{
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	// void LukkelEngine::TestUpdate(float updateFrequency) {}

	void LukkelEngine::render()
	{
		// int focused = glfwGetWindowAttrib(m_Window, GLFW_FOCUSED);
		renderImGuiData();
		m_Window->onUpdate();
	}

	void LukkelEngine::setMode(unsigned int setting)
	{
		m_GraphicsMode = setting;
		if (m_GraphicsMode == GRAPHICS_MODE_3D)   // 1
			GLCall(glEnable(GL_DEPTH_TEST));
		if (m_GraphicsMode == GRAPHICS_MODE_2D)	// 0
			GLCall(glDisable(GL_DEPTH_TEST));
	}

	void LukkelEngine::setBlending(unsigned int setting)
	{
		if (setting > 1)
			setting = DEFAULT_BLENDING_MODE;
		m_Blending = setting;
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
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


}
