#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

#include <Test/Test.h>			
#include <Test/TestClearColor.h>
#include <Test/TestTexture2D.h>
#include <Test/TestDrawTriangle.h>
#include <Test/TestDrawTriangle2.h>
#include <Test/TestDrawCube.h>
#include <Test/TestShader.h>
#include <Test/TestTexture.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <Display.h>			// TODO: Remove Display Class
#include <Camera.h>
#include <GLErrorHandler.h>
#include <Renderer.h>
#include <VertexBuffer.h>
// #if defined _WINDOWS_x64 || _WINDOWS_x86
//   #include <VertexBufferLayout_WINDOWS.h>
//   typedef VertexBufferLayout_WINDOWS VertexBufferLayout;
// #else
//   #include <VertexBufferLayout_LINUX.h>
//   typedef VertexBufferLayout_LINUX VertexBufferLayout;
// #endif
// #include <VertexBufferLayout.h>
#include <VertexBufferLayout.h>
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <Texture.h>

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
#define REFRESH_RATE_SIGMA       144
#define REFRESH_RATE_GIGACHAD    240
#define DEFAULT_FOV				 90.0f
#define DEFAULT_ZNEAR			 0.10f
#define DEFAULT_ZFAR			 1000.0f
#define DEFAULT_SCREEN_WIDTH     1600
#define DEFAULT_SCREEN_HEIGHT    1024

#define LOG(x) std::cout << "LOG: " << x << std::endl;

class LukkelEngine
{
public:
	LukkelEngine();
	LukkelEngine(unsigned int mode);
	LukkelEngine(unsigned int mode, unsigned int blending);
	~LukkelEngine();

	int SCREEN_WIDTH, SCREEN_HEIGHT;
	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu;

	GLFWwindow* GetWindow();
	void Render();
	void ScreenUpdate();
	void RenderImGuiData();
	void TestUpdate(float updateFrequency);
	void TestRunner(float updateFrequency);
	void Tick();
	void KeyInput(GLFWwindow* window, int key, int scanCode, int action, int mods);

// FIXME: CHANGE TO PRIVATE
private:
	Renderer renderer;
	GLFWwindow* window;
	unsigned int graphicsMode;
	unsigned int blending; 
	int status, status_GLFW, status_ImGui;
	int rotX, rotY, rotZ = 0.0f;

	int  Init(unsigned int graphicsMode, unsigned int blending);
	int  InitImGui();
	void SetMode(unsigned int setting);
	void SetBlending(unsigned int setting);
	int  RegisterTests();
	
};
