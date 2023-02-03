#ifndef _WINDOW_H
#define _WINDOW_H

#include <string>
#include <vector>

#include <LKErrorHandler.h>
#include <imgui/imgui.h>

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
		Window();
		~Window();

		virtual void onUpdate() = 0;
		virtual uint16_t getWidth() = 0;
		virtual uint16_t getHeight() = 0;

		virtual void setCallback() = 0; // FIXME
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;
		virtual void initImGui() = 0;
		virtual GLFWwindow* getWindow() const = 0;

		static Window* create(WindowProps& props = WindowProps());
	};
}
#endif /* _WINDOW_H */
