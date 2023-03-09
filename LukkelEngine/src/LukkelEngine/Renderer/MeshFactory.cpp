#include "LKpch.h"
#include "LukkelEngine/Renderer/MeshFactory.h"


namespace LukkelEngine {


	Mesh MeshFactory::createBox(glm::vec3& side)
	{

		float vertices[9 * 8] = {
			// Positions (x,y,z)  Texture coords     Color
			-0.5f, -0.5f,  0.5f,    0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 0.7, 
			 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,    0.2f, 0.5f, 0.0f, 0.7,
			-0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    1.0f, 0.0f, 1.0f, 0.7,
			 0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    0.3f, 0.5f, 0.0f, 0.7,
			-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f, 0.7,
			 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 0.5f, 0.5f, 0.7,
			-0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    0.7f, 0.0f, 1.0f, 0.7,
			 0.5f,  0.5f, -0.5f,    0.0f, 0.0f,    1.0f, 0.5f, 0.0f, 0.7
		};

		unsigned int indices[6 * 6] = {
			//Top
			2, 6, 7,
			2, 3, 7,
			//Bottom
			0, 4, 5,
			0, 1, 5,
			//Left
			0, 2, 6,
			0, 4, 6,
			//Right
			1, 3, 7,
			1, 5, 7,
			//Front
			0, 2, 3,
			0, 1, 3,
			//Back
			4, 6, 7,
			4, 5, 7
		};

		// Vertex Pos, Texture Coords, Vertex indices
		std::vector<int> layout = { 3, 2, 4 };
		Mesh mesh(vertices, indices, layout, 9*8, 36);

		return mesh;
	}

	// Mesh MeshFactory::createSphere(float radius)
	// {
	// }

	// void createMesh(float* vertices, unsigned int* indices)
	// {
	// }

}