#include <ErrorHandler.h>
#include <LukkelEngine.h>
#include <Window.h>
#include <Shader.h>

#define WIDTH  800
#define HEIGHT 600
#define ASSERT(x) //if (!(x)) __debugbreak();
#define LCall(x); //GLClearError(); x ; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#define LOG(x) std::cout << x << std::endl;


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")\nFUNCTION: " << function <<
            "\nFILE: " << file << "\nLINE: " << line << std::endl;
        return false;
    }
    return true;
}
int main()
{

    glfwInit();
    Window Window(WIDTH, HEIGHT, "LukkelEngine", 4, 3);
    glfwMakeContextCurrent(Window.m_Window);    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to init GLAD\n");
        return 1;
    }
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
   
    float positions[6] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
        -0.5f,  0.5f
    };
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    Shader shader = Shader("res/shaders/uColor.shader");
    //Shader shader = Shader("../../res/shaders/basic.shader");
    shader.bind();
    shader.setUniform4f("u_Color", 0.2f, 0.5f, 0.8f, 1.0f);

    while (!glfwWindowShouldClose(Window.m_Window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.bind();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(Window.m_Window);
        glfwPollEvents();
    }

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}
