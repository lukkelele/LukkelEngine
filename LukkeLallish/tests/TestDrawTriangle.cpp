#include <TestDrawTriangle.h>

namespace test {

	DrawTriangle::DrawTriangle()
	{
		VertexBuffer vbo(coordinates, 6 * sizeof(float));
		IndexBuffer ibo(indices, 3 * sizeof(float));
		layout.push<float>(2);
		vao.addBuffer(vbo, layout);

		Shader shader = Shader("res/shaders/basic.shader");
		shader.bind();
		shader.setUniform4f("u_Color", 0.3f, 0.8f, 0.3f, 1.0f);

		shader.unbind();

	}

	DrawTriangle::~DrawTriangle()
	{

	}

	void DrawTriangle::onImGuiRender()
	{

	}

	void DrawTriangle::onRender()
	{
		glClear(GL_COLOR_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT);
		Renderer renderer;

		vao.bind();
		shader.bind();
		ibo.bind();
		renderer.draw(vao, ibo, shader);

	}

	void DrawTriangle::onUpdate(float deltaTime)
	{

	}

}