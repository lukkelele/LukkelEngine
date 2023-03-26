#pragma once
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "LukkelEngine/Event/Event.h"

#include "GLFW/glfw3.h"


namespace LukkelEngine {

	struct WindowProps
	{
		std::string title;
		uint16_t width, height;
		WindowProps(const std::string& title = "LukkelEngine",
						 uint16_t width = 1920,
						 uint16_t height = 1080)
			: title(title), width(width), height(height){}
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		using EventCallbackFn = std::function<void(Event&)>;

		virtual void OnUpdate() = 0;
		virtual uint16_t GetWidth() = 0;
		virtual uint16_t GetHeight() = 0;

		// virtual void setInputLock(bool enabled = true) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual GLFWwindow* GetWindow() const = 0;
		static s_ptr<Window> Create(WindowProps& props = WindowProps());

		/* Static for platform independent window creation */
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

	protected:
		float m_ViewportWidth, m_ViewportHeight;
	};
}
