#include "LKpch.h"
#include "LukkelEngine/Debug/Test/TestDrawCube.h"

namespace LukkelEngine {

	namespace test {

		TestDrawCube::TestDrawCube()
		{
			float cube[] = {
				// Front side
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				// Back side
				-1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f 
			};

			int cubeIndices[] = {
				// front
				0, 1, 2,
				2, 3, 0,
				// right
				1, 5, 6,
				6, 2, 1,
				// back
				7, 6, 5,
				5, 4, 7,
				// left
				4, 0, 3,
				3, 7, 4,
				// bottom
				4, 5, 1,
				1, 0, 4,
				// top
				3, 2, 6,
				6, 7, 3
			};
			unsigned int countCubeVertices = sizeof(cube) / sizeof(float);
			std::cout << "Elements in 'cube': " << countCubeVertices << std::endl;
			m_VAO = std::make_unique<VertexArray>();
			m_VBO = std::make_unique<VertexBuffer>(cube, countCubeVertices * sizeof(float));
			m_IBO = std::make_unique<IndexBuffer>(cubeIndices, 50 * sizeof(float));
			VertexBufferLayout layout;
			layout.push<float>(3);
			m_VAO->addBuffer(*m_VBO, layout);

			m_Shader = std::make_unique<Shader>("assets/shaders/default3D.shader");
		}

		TestDrawCube::~TestDrawCube()
		{
		}

		void TestDrawCube::onUpdate(float deltaTime)
		{
		}

		void TestDrawCube::onRender()
		{
			m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
		}

		void TestDrawCube::onImGuiRender()
		{
		}

	}

}
