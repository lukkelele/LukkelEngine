#ifndef _TEST_SHADER_H
#define _TEST_SHADER_H

#include <Test/Test.h>
#include <vector>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Renderer.h>
#include <glm/ext.hpp>

namespace test {
	using namespace LukkelEngine;

	class TestShader : public Test
	{
	private:
		float c = 0.0f;    // variation color
		float inc = 0.01f; // increment step size

		float rectangle[8] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};
		unsigned int rect_indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

	public:
		TestShader();
		~TestShader();

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		// Shader m_Shader;
		// VertexArray m_VAO;
		// VertexBuffer m_VBO;
		// IndexBuffer m_IBO;
		std::unique_ptr<Renderer> m_Renderer;

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	};

}

#endif /* _TEST_SHADER_H */
