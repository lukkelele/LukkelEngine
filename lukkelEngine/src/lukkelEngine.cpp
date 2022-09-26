#include <lukkelEngine.h>


lukkelEngine::lukkelEngine()
{
	status = init(DEFAULT_GRAPHICS_MODE, DEFAULT_BLENDING_MODE);
}

lukkelEngine::lukkelEngine(unsigned int graphicsMode)
{
	status = init(graphicsMode, DEFAULT_BLENDING_MODE);
}

lukkelEngine::lukkelEngine(unsigned int graphicsMode, unsigned int blending)
{
	status = init(graphicsMode, blending);
}

lukkelEngine::~lukkelEngine()
{

}

int lukkelEngine::init(unsigned int graphicsMode, unsigned int blending)
{
    Display display = Display::Display(960, 540, "Lukkelele", 3, 3);
    window = display.getWindow();
	Renderer renderer;

	setMode(graphicsMode);
	setBlending(blending);

	// ImGui creation
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	return 1;
}

void lukkelEngine::setMode(unsigned int setting)
{
	graphicsMode = setting;
	if (graphicsMode == GRAPHICS_MODE_3D) 
		GLCall(glEnable(GL_DEPTH_TEST));
	if (graphicsMode == GRAPHICS_MODE_2D)
		GLCall(glDisable(GL_DEPTH_TEST));
}

void lukkelEngine::setBlending(unsigned int setting)
{
	blending = setting;
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

