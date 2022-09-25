#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <imgui/imgui.h>
//#include <imgui/imgui_impl_glfw_gl3.h>

/* Tests */
#include <TestClearColor.h>
#include <TestTexture2D.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <Display.h>
#include <GLErrorHandler.h>
#include <Renderer.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <Texture.h>


int main(void)
{
    Display display = Display::Display(960, 540, "Lukkelele", 3, 3);
    GLFWwindow* window = display.getWindow();
	Renderer renderer;

	// Enable blending
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// ImGui creation
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	// Create the test menu
	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;		// open menu initially

	// Register new test
	testMenu->registerTest<test::ClearColor>("Clear Color");
	testMenu->registerTest<test::Texture2D>("2D Texture");

	while (!glfwWindowShouldClose(window))
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		renderer.clear();
		
		ImGui_ImplGlfwGL3_NewFrame();
		if (currentTest)
		{
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

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());


		/* Swap front and back buffers and poll for events */
		GLCall(glfwSwapBuffers(window));
		GLCall(glfwPollEvents());
	}
	
	// Delete before exit
	delete currentTest;
	if (currentTest != testMenu)
		delete testMenu;
	
	ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    return 0;
}