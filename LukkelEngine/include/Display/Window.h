#ifndef _WINDOW_H
#define _WINDOW_H
#include <LKpch.h>

namespace LukkelEngine {
	
	struct WindowProperties
	{
		

	};

	class Window
	{
		Window();
		~Window();

		virtual void onUpdate() = 0;
		virtual unsigned int getWidth() = 0;
		virtual unsigned int getHeight() = 0;

		virtual void setCallback() = 0; // FIXME
		virtual void setVSync(unsigned int enable) = 0;
		virtual unsigned int isVSync() = 0;

		static Window* create()
	};

}

#endif /* _WINDOW_H */
