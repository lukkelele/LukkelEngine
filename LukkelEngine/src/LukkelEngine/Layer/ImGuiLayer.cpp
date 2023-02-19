#include "LukkelEngine/Layer/ImGuiLayer.h"
#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::onAttach()
	{
		LKLOG_TRACE("ImGuiLayer attaching...");
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		// Enable keyboard
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		Application& app = Application::get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow());
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();
		
		registerTests();
	}

	/*
		As some layers (e.g TestLayer in Sandbox) uses ImGui drawing functionality
		the program can crash if ImGuiLayer is below such a layer. Other lays SHOULD
		be in front of this one though, but to keep the entire ImGui operations to one
		single layer, some boolean statement could be used to evaluate the imgui operations
		beforehand. It is important to note that the order does play a vital role because
		of the different renders that take place e.g so that the clear color test doesn't
		override a cube or something
	*/
	void ImGuiLayer::onUpdate(float ts)
	{
		renderTestMenu();

	}

	void ImGuiLayer::registerTests()
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
	}

	void ImGuiLayer::renderTestMenu()
	{
		if (currentTest) {
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

	void ImGuiLayer::begin()
	{
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		float width = (float) app.getViewportWidth();
		float height = (float) app.getViewportHeight();
		io.DisplaySize = ImVec2(width, height);
	}

	void ImGuiLayer::onImGuiRender()
	{
		ImGui::InputText("string", m_Buffer, IM_ARRAYSIZE(m_Buffer));
	}

	void ImGuiLayer::onEvent(LukkelEngine::Event& e)
	{

	}

	void ImGuiLayer::onDetach()
	{
		ImGui::DestroyContext();
	}

}