#pragma once
#include "LukkelEngine/Core/Window.h"
#include "LukkelEngine/Event/ApplicationEvent.h"

namespace LukkelEngine {

    class Linux_Window : public Window
        {
        public:
            Linux_Window(WindowProps& properties);
            virtual ~Linux_Window(); // virtual deconstructor for derived class

            inline uint16_t getWidth() override { return m_Data.width; }
            inline uint16_t getHeight() override { return m_Data.height; }
            GLFWwindow* getWindow() const override;

            void onUpdate() override;
            void setEventCallback(const EventCallbackFn& callback) override { m_Data.eventCallback = callback; }
            void setVSync(bool enabled) override;
            bool isVSync() const override;

            void setInputLock(bool enabled = true) override;
            void init(WindowProps& properties);
            void exit();

        // FIXME: set private 
        public:
            GLFWwindow* m_Window;
            bool m_InputLock = false;

            struct WindowData
            {
                std::string title;
                uint16_t width, height;
                bool VSync;
                EventCallbackFn eventCallback;
            };

            WindowData m_Data;
	};
}

