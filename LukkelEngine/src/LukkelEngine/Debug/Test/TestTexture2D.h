#pragma once
#include "LukkelEngine/Debug/Test/Test.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBufferLayout.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Renderer/Shader.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace LukkelEngine {

	namespace test {

		class TestTexture2D : public Test
		{
		public:
			TestTexture2D();
			~TestTexture2D();

			void OnUpdate(float deltaTime) override;
			void onRender() override;
			void OnImGuiRender() override;

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

}
