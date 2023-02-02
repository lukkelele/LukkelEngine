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

public:
	Keyboard();
	~Keyboard();

	void bind();
	void unbind();

	int keyPressed();
	void keyInput(GLFWwindow* window, int key, int scanCode, int action, int mods);
	static void keyInputStatic(GLFWwindow* window, int key, int scanCode, int action, int mods);
};

#endif /* _KEYBOARD_H */
