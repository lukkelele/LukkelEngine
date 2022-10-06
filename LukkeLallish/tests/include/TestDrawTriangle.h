#pragma once
#include <Test.h>
#include <vector>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Renderer.h>

namespace test {

	class DrawTriangle : public Test
	{
	public:
		DrawTriangle();
		~DrawTriangle();

		VertexArray vao;
		VertexBuffer vbo;
		VertexBufferLayout layout;
		Shader shader;
		IndexBuffer ibo;

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
		
	private:
		float coordinates[6] = {
			-0.5f, 0.0f,
			 0.5f, 0.0f,
			 0.0f, 0.5f
		};
	
		int indices[3] = {
			0, 1, 2
		};

	};



}
