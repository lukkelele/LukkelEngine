#ifndef _TEST_TEXTURE_H
#define _TEST_TEXTURE_H

#include <Test/Test.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Texture.h>
#include <Renderer.h>
#include <glm/ext.hpp>


namespace test {

	class TestTexture : public Test
	{
	private:
		float c = 0.0f;    // variation color
		float inc = 0.01f; // increment step size

		// VERTEX COORD | TEXTURE COORDINATES
		float rectangle[16] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};
		unsigned int rect_indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

	public:
		TestTexture();
		~TestTexture();

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Renderer> m_Renderer;

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	};

}


#endif /* _TEST_TEXTURE_H */
