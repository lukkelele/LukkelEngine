#ifndef _TEST_TEXTURE2D_H
#define _TEST_TEXTURE2D_H

#include <Test.h>
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

	class Texture2D : public Test
	{
	public:
		Texture2D();
		~Texture2D();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;

	};

}

#endif /* _TEST_CLEARCOLOR_H */