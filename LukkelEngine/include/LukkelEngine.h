#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

#include <Test.h>			
#include <TestClearColor.h>
#include <TestTexture2D.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <Display.h>			// TODO: Remove Display Class
#include <GLErrorHandler.h>
#include <Renderer.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <Texture.h>
#include <Mesh.h>

/* ENGINE DEFAULTS */
#define BLENDING_DISABLED		 0  // DISABLE BLENDING		
#define BLENDING_ENABLED         1	// ENABLE BLENDING		
#define GRAPHICS_MODE_2D		 0	// 2D GRAPHICS MODE     
#define GRAPHICS_MODE_3D		 1  // 3D GRAPHICS MODE 
#define DEFAULT_GRAPHICS_MODE	 GRAPHICS_MODE_3D		
#define DEFAULT_BLENDING_MODE	 1  // SET DEFAULT BLENDING MODE 

/* CLIENT DEFAULTS */
#define ZERO_UPDATE_FREQUENCY    0.0f
#define DEFAULT_REFRESH_RATE	 60
#define DEFAULT_FOV				 90.0f
#define DEFAULT_ZNEAR			 0.10f
#define DEFAULT_ZFAR			 1000.0f
#define DEFAULT_SCREEN_WIDTH     1600
#define DEFAULT_SCREEN_HEIGHT    1024


class lukkelEngine
{
public:
	lukkelEngine();
	lukkelEngine(unsigned int mode);
	lukkelEngine(unsigned int mode, unsigned int blending);
	~lukkelEngine();

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu;

	GLFWwindow* getWindow();
	void render();
	void screenUpdate();
	void renderImGuiData();
	void testUpdate(float updateFrequency);
	void testRunner(float updateFrequency);
	void testRender();
	void tick();
	void run();

private:
	Renderer renderer;
	GLFWwindow* window;
	unsigned int graphicsMode;
	unsigned int blending; 
	int status;
	int status_GLFW;
	int status_ImGui;

	int  init(unsigned int graphicsMode, unsigned int blending);
	int  initImGui();
	void setMode(unsigned int setting);
	void setBlending(unsigned int setting);
	int  registerTests();
	
	
};