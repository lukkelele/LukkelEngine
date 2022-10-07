#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ErrorHandler.h>
#include <Window.h>


class LukkelEngine
{
public:
    LukkelEngine();
    ~LukkelEngine();

    int initGlfw();
    int initGlad();
    int initImGui();
    

private:
    int m_Status;
    Window m_Window;

};
