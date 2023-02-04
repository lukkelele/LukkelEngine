#pragma once

/* LIBRARIES */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

/* CORE FUNCTIONALITY */
#include <Core/Log.h>
#include <Core/LukkelCore.h>
#include <Core/LKErrorHandler.h>
#include <Core/Filesystem.h>
#include <Core/Buffer.h>

/* EVENTS */
#include <Event/ApplicationEvent.h>
// #include <Event/Event.h>
#include <Event/KeyEvent.h>
#include <Event/MouseEvent.h>

/* I/O */
#include <Display/Window.h>
#include <Input/Keyboard.h>

/* RENDERER */
#include <Renderer/Camera.h>
#include <Renderer/Renderer.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/VertexBufferLayout.h>
#include <Renderer/VertexArray.h>
#include <Renderer/IndexBuffer.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>

/* TESTS */
#include <Test/Test.h>			
#include <Test/TestClearColor.h>
#include <Test/TestTexture2D.h>
#include <Test/TestDrawTriangle.h>
#include <Test/TestDrawTriangle2.h>
#include <Test/TestDrawCube.h>
#include <Test/TestShader.h>
#include <Test/TestTexture.h>
#include <Test/TestKeyInput.h>



#define WIDTH 1600
#define HEIGHT 1024
#define TITLE "LukkelEngine"
#define MAJOR_VERSION 3
#define MINOR_VERSION 3

/* ENGINE DEFAULTS */
#define BLENDING_DISABLED		 0  // DISABLE BLENDING		
#define BLENDING_ENABLED         1	// ENABLE BLENDING		
#define GRAPHICS_MODE_2D		 0	// 2D GRAPHICS MODE     
#define GRAPHICS_MODE_3D		 1  // 3D GRAPHICS MODE 
#define DEFAULT_GRAPHICS_MODE	 GRAPHICS_MODE_3D		
#define DEFAULT_BLENDING_MODE	 1  // SET DEFAULT BLENDING MODE 

/* CLIENT DEFAULTS */
#define ZERO_UPDATE_FREQUENCY    0.0f
#define REFRESH_RATE_DEFAULT	 60
#define REFRESH_RATE_SIGMA       144
#define REFRESH_RATE_GIGACHAD    240
#define DEFAULT_FOV				 90.0f
#define DEFAULT_ZNEAR			 0.10f
#define DEFAULT_ZFAR			 1000.0f
#define DEFAULT_SCREEN_WIDTH     1600
#define DEFAULT_SCREEN_HEIGHT    1024

#define LOG(x) std::cout << "LOG: " << x << std::endl;

namespace LukkelEngine {

	class LukkelEngine
	{
	public:
		LukkelEngine();
		~LukkelEngine();

		// int SCREEN_WIDTH, SCREEN_HEIGHT;
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu;

		void init(unsigned int graphicsMode, bool blending);
		void render();
		void screenUpdate();
		void renderImGuiData();
		void testRunner(float updateFrequency);
		GLFWwindow* getWindow();

	private:
		Renderer m_Renderer;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Keyboard> m_Keyboard;
		// Keyboard m_Keyboard;
		unsigned int m_GraphicsMode;
		unsigned int m_Blending; 
		int status_GLFW;
		int status_ImGui;
		// float rotX, rotY, rotZ = 0.0f;

		int  initImGui();
		void setMode(unsigned int setting);
		void setBlending(unsigned int setting);
		int  registerTests();
		
	};
}
