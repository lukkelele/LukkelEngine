#include "LukkelEngine/Core/Application.h"
#include "TestLayer.h"
#include "TestCoordinates.h"

// #define LE typeid(LukkelEngine::LukkelEngine).name() // FOR LukkelEngine short name

class Sandbox : public LukkelEngine::Application
{
public:
	Sandbox(const LukkelEngine::ApplicationDetails& details = LukkelEngine::ApplicationDetails())
		: LukkelEngine::Application(details)
	{
	}

	~Sandbox()
	{
	}

};

int main()
{
	std::cout << "Hello World!" << std::endl;
	Sandbox app;
	GLFWwindow* window = app.getWindow();
	glEnable(GL_DEPTH_TEST);
	TestLayer layer;
	app.pushLayer(&layer); // heap bug at LayerStack destructor

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	LukkelEngine::Renderer renderer;
	LukkelEngine::VertexArray vao = LukkelEngine::VertexArray();

	// LukkelEngine::VertexBuffer vbo = LukkelEngine::VertexBuffer(rectangle_tex, (sizeof(rectangle_tex) / (sizeof(float)) * sizeof(float)));
	// LukkelEngine::IndexBuffer ibo = LukkelEngine::IndexBuffer(rect_indices_tex, (sizeof(rect_indices_tex) / sizeof(unsigned int)) * sizeof(unsigned int));
	LukkelEngine::VertexBuffer vbo = LukkelEngine::VertexBuffer(rectangle, (sizeof(rectangle) / (sizeof(float)) * sizeof(float)));
	LukkelEngine::IndexBuffer ibo = LukkelEngine::IndexBuffer(rectangle_indices, (sizeof(rectangle_indices) / sizeof(unsigned int)) * sizeof(unsigned int));

	LukkelEngine::VertexBufferLayout layout;
	layout.push<float>(2);
	// layout.push<float>(2);

	vao.addBuffer(vbo, layout);
	//LukkelEngine::Texture texture = LukkelEngine::Texture("res/textures/tinder_logo.png");
	//LukkelEngine::Shader shader = LukkelEngine::Shader("res/shaders/default3D.shader");
	//LukkelEngine::Shader shader = LukkelEngine::Shader("res/shaders/basic2.shader");
	LukkelEngine::Shader shader = LukkelEngine::Shader("res/shaders/3D/color3D.shader");
	shader.bind();
	shader.setUniform4f("u_Color", 0.5f, 0.8f, 0.5f, 1.0f);
	glm::vec3 translationA(0, 0, 5);

	LukkelEngine::Camera cam(60, 800, 600, 0.1, 100.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
	glm::mat4 proj = cam.getProjectionMatrix();
	glm::mat4 view = cam.getViewMatrix();
	glm::mat4 mvp = proj * view * model;

	glm::vec3 color(1, 0.5, 1);

	float sliderMax = 30.0f;
	float colorSliderMax = 1.0f;

	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::SliderFloat3("Translation A", &translationA.x, 0, sliderMax); 
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		// Color slider for the object -> color.x will include rest of vector as well
		ImGui::SliderFloat3("object rgb color", &color.x, 0, colorSliderMax);

		model = glm::translate(glm::mat4(1.0f), translationA);
		mvp = proj * view * model;
		shader.bind();
		shader.setUniformMat4f("camMatrix", mvp);
		shader.setUniform4f("u_Color", color.x, color.y, color.z, 1.0f);

		renderer.draw(vao, ibo, shader);
		renderer.drawImGui();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	LKLOG_CRITICAL("SANDBOX terminated!");
	return 0;
}