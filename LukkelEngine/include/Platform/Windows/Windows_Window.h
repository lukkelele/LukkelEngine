#include <Display/Window.h>

namespace LukkelEngine {

	class Windows_Window : public Window
	{
	public:
		Windows_Window(WindowProps& properties);
		virtual ~Windows_Window(); // virtual deconstructor for derived class

		inline uint16_t getWidth() override { return m_Data.width; }
		inline uint16_t getHeight() override { return m_Data.height; }

		void onUpdate() override;
		inline void setCallback() override;
		void setVSync(bool enabled) override;
		bool isVSync() const override;
		void initImGui() override;

		GLFWwindow* getWindow() const override;

	private:
		GLFWwindow* m_Window;

		virtual void init(WindowProps& properties);
		virtual void exit();

		struct WindowData
		{
			std::string title;
			uint16_t width, height;
			bool VSync;
			// EVENT CALLBACK HERE
		};
		WindowData m_Data;
	};
}
