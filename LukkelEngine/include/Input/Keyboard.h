#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <GLErrorHandler.h>
#include <glfw/glfw3.h>

class Keyboard
{
private:
	float m_RotX = 0;
	float m_RotY = 0;
	float m_RotationSpeed = 5.0f;
	GLFWwindow* m_WindowReference;

public:
	Keyboard();
	Keyboard(GLFWwindow* window);
	~Keyboard();

	void Bind(GLFWwindow* window);
	void Unbind();

	int KeyPressed();
	void Input(GLFWwindow* window, int key, int scanCode, int action, int mods);
	static void Input_static(GLFWwindow* window, int key, int scanCode, int action, int mods);
};

#endif /* _KEYBOARD_H */
