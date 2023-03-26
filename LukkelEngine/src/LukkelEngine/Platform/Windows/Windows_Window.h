#pragma once
#include "LukkelEngine/Core/Window.h"

namespace LukkelEngine {

	class Windows_Window : public Window
	{
	public:
		Windows_Window(WindowProps& properties);
		virtual ~Windows_Window(); // virtual deconstructor for derived class

		inline uint16_t GetWidth() override { return m_Data.width; }
		inline uint16_t GetHeight() override { return m_Data.height; }
		GLFWwindow* GetWindow() const override;

		void OnUpdate() override;
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void Init(WindowProps& properties);
		void Exit();

	// FIXME: set private 
	public:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string title;
			uint16_t width, height;
			bool vsync;
			EventCallbackFn eventCallback;
		};
		WindowData m_Data;
	};
}
