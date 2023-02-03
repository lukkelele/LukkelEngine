#pragma once

#include <Test/Test.h>
#include <memory>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <VertexArray.h>
#include <VertexBufferLayout.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <Texture.h>
#include <Shader.h>


/*
	TEST FILE, 2D TEXTURES
*/


namespace test {

	using namespace LukkelEngine;

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Renderer> m_Renderer;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;

	};

}
