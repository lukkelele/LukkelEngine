#include <LukkelEngine.h>

namespace LukkelEngine {

	LukkelEngine::LukkelEngine()
	{
		status = Init(DEFAULT_GRAPHICS_MODE, DEFAULT_BLENDING_MODE);
	}

	LukkelEngine::LukkelEngine(unsigned int graphicsMode)
	{
		status = Init(graphicsMode, DEFAULT_BLENDING_MODE);
	}

	LukkelEngine::LukkelEngine(unsigned int graphicsMode, unsigned int blending)
	{
		status = Init(graphicsMode, blending);
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

	GLFWwindow* LukkelEngine::GetWindow() {	return m_Window; }

	int LukkelEngine::Init(unsigned int graphicsMode, unsigned int blending)
	{
		// Initiate GLFW and GLEW
		glfwInit();
		m_Window = initDisplay(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "LukkelEngine", 3, 3);
		initGlew();
		
		SetMode(graphicsMode);		// GRAPHICS MODE
		SetBlending(blending);		// BLENDING 
		status_ImGui = InitImGui(); // IMGUI

		// Initiate I/O
		LOG("Creating I/O modules...");
		Keyboard m_Keyboard;
		m_Keyboard.Bind(m_Window);
		// GLCall(glfwSetKeyCallback(m_Window, m_Keyboard.));
		
		// Test registration
		RegisterTests();

		return 1;
	}

	int LukkelEngine::RegisterTests()
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

	void LukkelEngine::ScreenUpdate()
	{
		m_Renderer.Clear();
	}

	int LukkelEngine::InitImGui()
	{
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(m_Window, true);
		ImGui::StyleColorsDark();
		return 1;
	}

	void LukkelEngine::RenderImGuiData()
	{
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	// void LukkelEngine::TestUpdate(float updateFrequency) {}

	void LukkelEngine::Render()
	{
		int focused = glfwGetWindowAttrib(m_Window, GLFW_FOCUSED);
		if (glfwGetCurrentContext() == m_Window) {
			RenderImGuiData();
			GLCall(glfwSwapBuffers(m_Window));
			GLCall(glfwPollEvents());
		}
	}

	void LukkelEngine::SetMode(unsigned int setting)
	{
		m_GraphicsMode = setting;
		if (m_GraphicsMode == GRAPHICS_MODE_3D)   // 1
			GLCall(glEnable(GL_DEPTH_TEST));
		if (m_GraphicsMode == GRAPHICS_MODE_2D)	// 0
			GLCall(glDisable(GL_DEPTH_TEST));
	}

	void LukkelEngine::SetBlending(unsigned int setting)
	{
		if (setting > 1)
			setting = DEFAULT_BLENDING_MODE;
		m_Blending = setting;
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void LukkelEngine::TestRunner(float updateFrequency)
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
