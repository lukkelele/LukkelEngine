#pragma once

#include <LukkelEngine/Core/PlatformDetection.h>
#include <LukkelEngine/Core/Log.h>

/* LIBRARIES */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

/* CORE FUNCTIONALITY */
#include <LukkelEngine/Core/Base.h>
#include <LukkelEngine/Core/Application.h>
#include <LukkelEngine/Core/LKErrorHandler.h>
#include <LukkelEngine/Core/Filesystem.h>
#include <LukkelEngine/Core/Buffer.h>

/* EVENTS */
#include <LukkelEngine/Event/ApplicationEvent.h>
#include <LukkelEngine/Event/KeyEvent.h>
#include <LukkelEngine/Event/MouseEvent.h>

/* I/O */
#include <LukkelEngine/Core/Window.h>
#include <LukkelEngine/Input/Keyboard.h>

/* RENDERELukkelEngine/R */
#include <LukkelEngine/Renderer/Camera.h>
#include <LukkelEngine/Renderer/Renderer.h>
#include <LukkelEngine/Renderer/VertexBuffer.h>
#include <LukkelEngine/Renderer/VertexBufferLayout.h>
#include <LukkelEngine/Renderer/VertexArray.h>
#include <LukkelEngine/Renderer/IndexBuffer.h>
#include <LukkelEngine/Renderer/Shader.h>
#include <LukkelEngine/Renderer/Texture.h>

/* TESTS */
#include <LukkelEngine/Test/Test.h>			
#include <LukkelEngine/Test/TestClearColor.h>
#include <LukkelEngine/Test/TestTexture2D.h>
#include <LukkelEngine/Test/TestDrawTriangle.h>
#include <LukkelEngine/Test/TestDrawTriangle2.h>
#include <LukkelEngine/Test/TestDrawCube.h>
#include <LukkelEngine/Test/TestShader.h>
#include <LukkelEngine/Test/TestTexture.h>
#include <LukkelEngine/Test/TestKeyInput.h>



#define WIDTH 1600
#define HEIGHT 1024
#define TITLE "LukkelEngine"
#define MAJOR_VERSION 3
#define MINOR_VERSION 3

/* ENGINE DEFAULTS */
#define LK_BLENDING_DISABLED		0	// DISABLE BLENDING		
#define LK_BLENDING_ENABLED         1	// ENABLE BLENDING		
#define LK_GRAPHICS_MODE_2D			0	// 2D GRAPHICS MODE     
#define LK_GRAPHICS_MODE_3D			1	// 3D GRAPHICS MODE 
#define LK_DEFAULT_GRAPHICS_MODE	LK_GRAPHICS_MODE_3D		
#define LK_DEFAULT_BLENDING_MODE	LK_BLENDING_ENABLED

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

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu;

		void init(uint8_t graphicsMode = LK_GRAPHICS_MODE_3D,
				  bool blending = LK_BLENDING_ENABLED);
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
		uint8_t m_GraphicsMode;
		uint8_t m_Blending; 
		int status_GLFW;
		int status_ImGui;

		int  initImGui();
		void setMode(unsigned int setting);
		void setBlending(unsigned int setting);
		void registerTests();
		
	};
}
