#pragma once

#include <string>
#include <vector>

#include "LukkelEngine/Core/LKErrorHandler.h"
#include "LukkelEngine/Event/Event.h"

#include "GLFW/glfw3.h"

namespace LukkelEngine {

	struct WindowProps
	{
		std::string title;
		uint16_t width, height;
		WindowProps(const std::string& title = "LukkelEngine",
						 uint16_t width = 800,
						 uint16_t height = 600)
			: title(title), width(width), height(height){}
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		using EventCallbackFn = std::function<void(Event&)>;

		virtual void onUpdate() = 0;
		virtual uint16_t getWidth() = 0;
		virtual uint16_t getHeight() = 0;

		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual GLFWwindow* getWindow() const = 0;
		static s_ptr<Window> create(WindowProps& props = WindowProps());

		/* Static for platform independent window creation */
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;

		float m_ViewportWidth, m_ViewportHeight;
	};
}
