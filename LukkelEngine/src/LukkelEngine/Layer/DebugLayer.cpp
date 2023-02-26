#include "LKpch.h"
#include "LukkelEngine/Layer/DebugLayer.h"

#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {
	
	DebugLayer::DebugLayer()
		: Layer("DebugLayer")
	{
		registerTests();
	}

	void DebugLayer::onUpdate(float ts)
	{
		renderTestMenu();
	}

	void DebugLayer::onImGuiRender()
	{
		auto cam = Application::get().getScene()->getCamera();
		ImGui::Checkbox("Draw lines", &Renderer::s_DrawMode);
		ImGui::Checkbox("Enable mouse", &Application::get().getCamera()->m_MouseEnabled); // FIXME
		ImGui::SliderFloat("Camera speed", &cam->m_Speed, 0.010f, 2.0f);
		ImGui::SliderFloat("FOV", &cam->m_FOV, 25.0f, 120.0f);
		ImGui::SliderFloat3("Camera position", &cam->m_Position.x, -40.0f, 40.0f);
		// ImGui::Text("Average FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); 
	}

	void DebugLayer::renderTestMenu()
	{
		if (currentTest)
		{
			currentTest->onUpdate(0.0f);
			currentTest->onRender();
			ImGui::Begin("Tests");
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

	void DebugLayer::registerTests()
	{
		testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
		testMenu->registerTest<test::TestClearColor>("Color picker");
		testMenu->registerTest<test::TestTexture2D>("2D Texture");
		testMenu->registerTest<test::TestDrawTriangle>("Draw 2D triangle");
		testMenu->registerTest<test::TestDrawTriangle2>("Draw 2D triangle v2");
		testMenu->registerTest<test::TestShader>("Shader test");
	}

}