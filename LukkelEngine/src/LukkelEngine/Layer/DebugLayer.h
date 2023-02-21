#pragma once
#include "LukkelEngine/Core/Layer.h"
#include "LukkelEngine/Test/Test.h"
#include "LukkelEngine/Test/TestClearColor.h"
#include "LukkelEngine/Test/TestTexture2D.h"
#include "LukkelEngine/Test/TestDrawTriangle.h"
#include "LukkelEngine/Test/TestDrawTriangle2.h"
#include "LukkelEngine/Test/TestDrawCube.h"
#include "LukkelEngine/Test/TestShader.h"

#include "imgui/imgui.h"

namespace LukkelEngine {

	class DebugLayer : public Layer
	{
	public:
		DebugLayer()
		{
			registerTests();
		}
		~DebugLayer() = default;

		void onUpdate(float ts)
		{
			renderTestMenu();
		}

		void renderTestMenu()
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

		void registerTests()
		{
			testMenu = new test::TestMenu(currentTest);
			currentTest = testMenu;
			testMenu->registerTest<test::TestClearColor>("Clear Color");
			testMenu->registerTest<test::TestTexture2D>("2D Texture");
			testMenu->registerTest<test::TestDrawTriangle>("Draw 2D triangle");
			testMenu->registerTest<test::TestDrawTriangle2>("Draw 2D triangle v2");
			testMenu->registerTest<test::TestDrawCube>("Draw 3D cube");
			testMenu->registerTest<test::TestShader>("Shader test");
		}

	private:
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu;
	};
}
