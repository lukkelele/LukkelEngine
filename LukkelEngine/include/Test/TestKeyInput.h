#ifndef _TEST_KEYINPUT_H
#define _TEST_KEYINPUT_H
#include <Test/Test.h>
#include <glfw/glfw3.h>
#include <vector>

namespace test {

	class TestKeyInput : public Test
	{
	private:
		float m_rotX; // x - rotation
		float m_rotY; // y - rotation
		// GLFWwindow* m_Window;
		std::unique_ptr<GLFWwindow*> m_Window;
		std::vector<int> m_KeysPressedCache;
	public:
		TestKeyInput();
		TestKeyInput(GLFWwindow* window);
		~TestKeyInput();

		void SetWindow(GLFWwindow& window);
		void KeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}
#endif /* _TEST_KEYINPUT_H */
