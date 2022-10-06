#include <LukkelEngine.h>


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
	
	ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
	glfwTerminate();
}

GLFWwindow* LukkelEngine::getWindow() {	return window; }

int LukkelEngine::init(unsigned int graphicsMode, unsigned int blending)
{
    // Initiate GLFW and GLEW
	glfwInit();
	window = initDisplay(960, 540, "LukkelEngine",  3, 3);
    initGlew();
	
	setMode(graphicsMode);		// GRAPHICS MODE
	setBlending(blending);		// BLENDING 
	status_ImGui = initImGui(); // IMGUI

	// TEST MENU
	testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;
	testMenu->registerTest<test::ClearColor>("Clear Color");
	testMenu->registerTest<test::Texture2D>("2D Texture");
	testMenu->registerTest<test::DrawTriangle>("Draw 2D triangle");

	return 1;
}

void LukkelEngine::screenUpdate()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	renderer.clear();
	ImGui_ImplGlfwGL3_NewFrame();
}

int LukkelEngine::initImGui()
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
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
	GLCall(glfwSwapBuffers(window));
	GLCall(glfwPollEvents());
}

void LukkelEngine::setMode(unsigned int setting)
{
	graphicsMode = setting;
	if (graphicsMode == GRAPHICS_MODE_3D)   // 1
		GLCall(glEnable(GL_DEPTH_TEST));
	if (graphicsMode == GRAPHICS_MODE_2D)	// 0
		GLCall(glDisable(GL_DEPTH_TEST));
}

void LukkelEngine::setBlending(unsigned int setting)
{
	if (setting > 1)
		setting = DEFAULT_BLENDING_MODE;
	blending = setting;
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void LukkelEngine::testRunner(float updateFrequency)
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

