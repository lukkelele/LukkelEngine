#include <LukkelEngine.h>

namespace LukkelEngine {

	LukkelEngine::LukkelEngine()
	{
		m_Blending = 1;
	}

	LukkelEngine::~LukkelEngine()
	{
		// TERMINATE ALL 
		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
		// Move this to terminate ImGui and opengl inside Window
		ImGui_ImplGlfwGL3_Shutdown(); // FIXME
		ImGui::DestroyContext();
		glfwTerminate();
	}

	void LukkelEngine::init(unsigned int graphicsMode, bool blending)
	{
		/* Enable logging */
		Log::init();
		LK_TRACE("Creating window ({0}x{1})", DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
		m_Window = std::unique_ptr<Window>(Window::create());
		initImGui();

		// Initiate I/O
		LK_TRACE("Attaching I/O modules...");
		Keyboard m_Keyboard;
		m_Keyboard.Bind(m_Window->getWindow());
		// GLCall(glfwSetKeyCallback(m_Window, m_Keyboard.));
		
		// Test registration
		LK_TRACE("Registering tests...");
		registerTests();
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
		m_Renderer.clear();
	}

	int LukkelEngine::initImGui()
	{
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(m_Window->getWindow(), true);
		ImGui::StyleColorsDark();
		return 1;
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
