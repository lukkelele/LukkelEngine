#ifndef _TEST_SHADER_H
#define _TEST_SHADER_H

#include <vector>
#include "LukkelEngine/Test/Test.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/VertexBufferLayout.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "glm/ext.hpp"

namespace LukkelEngine {
	namespace test {

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
			std::unique_ptr<Renderer> m_Renderer;

			void onUpdate(float deltaTime) override;
			void onRender() override;
			void onImGuiRender() override;

		};
	}
}

#endif /* _TEST_SHADER_H */
