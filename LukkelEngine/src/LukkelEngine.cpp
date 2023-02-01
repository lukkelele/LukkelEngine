#include <LukkelEngine.h>


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

GLFWwindow* LukkelEngine::GetWindow() {	return window; }

int LukkelEngine::Init(unsigned int graphicsMode, unsigned int blending)
{
	SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
	SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;
    // Initiate GLFW and GLEW
	glfwInit();
	window = initDisplay(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "LukkelEngine",  3, 3);
    initGlew();
	
	SetMode(graphicsMode);		// GRAPHICS MODE
	SetBlending(blending);		// BLENDING 
	// FIXME
	status_ImGui = InitImGui(); // IMGUI

	// TEST MENU
	testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;
	testMenu->registerTest<test::TestClearColor>("Clear Color");
	testMenu->registerTest<test::TestTexture2D>("2D Texture");
	testMenu->registerTest<test::TestDrawTriangle>("Draw 2D triangle");
	testMenu->registerTest<test::TestDrawTriangle2>("Draw 2D triangle v2");
	testMenu->registerTest<test::TestDrawCube>("Draw 3D cube");
	testMenu->registerTest<test::TestShader>("Shader test");
	testMenu->registerTest<test::TestTexture>("Texture testing");
	LOG("Tests created!");

	// USER INPUT
	GLCall(glfwSetWindowUserPointer(window, this));
	GLCall(glfwSetInputMode(window, GLFW_STICKY_KEYS, 1));
	GLCall(glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT));
	GLCall(glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000));

	return 1;
}

void LukkelEngine::ScreenUpdate()
{
	renderer.Clear();
}

int LukkelEngine::InitImGui()
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
	return 1;
}

void LukkelEngine::RenderImGuiData()
{
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void LukkelEngine::TestUpdate(float updateFrequency) {}

void LukkelEngine::Render()
{
	RenderImGuiData();
	GLCall(glfwSwapBuffers(window));
	GLCall(glfwPollEvents());
}

void LukkelEngine::SetMode(unsigned int setting)
{
	graphicsMode = setting;
	if (graphicsMode == GRAPHICS_MODE_3D)   // 1
		GLCall(glEnable(GL_DEPTH_TEST));
	if (graphicsMode == GRAPHICS_MODE_2D)	// 0
		GLCall(glDisable(GL_DEPTH_TEST));
}

void LukkelEngine::SetBlending(unsigned int setting)
{
	if (setting > 1)
		setting = DEFAULT_BLENDING_MODE;
	blending = setting;
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

void LukkelEngine::KeyInput(GLFWwindow * window, int key, int scanCode, int action, int mods)
{
	const GLfloat rotationSpeed = 10;
	LOG(key);
	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key) {
		case GLFW_KEY_UP:
			rotX -= rotationSpeed;
			break;
		case GLFW_KEY_DOWN:
			rotX += rotationSpeed;
			break;
		case GLFW_KEY_RIGHT:
			rotY += rotationSpeed;
			break;
		case GLFW_KEY_LEFT:
			rotY -= rotationSpeed;
			break;
		}
	}
}

