#include <LukkelEngine/Core/Application.h>

namespace LukkelEngine {

	Application::Application()
	{
		Log::init();
		LK_CORE_CRITICAL("Starting application");
		m_Window = Window::create();
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(m_Window->getWindow(), true);
		ImGui::StyleColorsDark();
		m_ImGuiInitialized = true;
		registerTests();
	}

	Application::~Application()
	{
		LK_CORE_CRITICAL("Terminating application");
	}

	void Application::run(bool test)
	{
		LK_CORE_INFO("App->run()");
		LK_CORE_INFO("Testing: {0}", test);
		while (!glfwWindowShouldClose(m_Window->getWindow()))
		{
			m_Renderer->clear();
			testRunner();
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

}
