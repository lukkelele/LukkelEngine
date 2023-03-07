#include "LKpch.h"
#include "LukkelEngine/Renderer/MeshFactory.h"


namespace LukkelEngine {


	Mesh MeshFactory::createBox(glm::vec3& side)
	{

		float vertices[] = {
			-side.x / 2.0f, -side.y / 2.0f,  side.z / 2.0f,
			 side.x / 2.0f, -side.y / 2.0f,  side.z / 2.0f, 
			 side.x / 2.0f,  side.y / 2.0f,  side.z / 2.0f, 
			-side.x / 2.0f,  side.y / 2.0f,  side.z / 2.0f, 
			-side.x / 2.0f, -side.y / 2.0f, -side.z / 2.0f, 
			 side.x / 2.0f, -side.y / 2.0f, -side.z / 2.0f, 
			 side.x / 2.0f,  side.y / 2.0f, -side.z / 2.0f, 
			-side.x / 2.0f,  side.y / 2.0f, -side.z / 2.0f 
		};

		unsigned int indices[] = {
			0, 1, 2, 
		    2, 3, 0, 
		    1, 5, 6, 
		    6, 2, 1, 
		    7, 6, 5, 
		    5, 4, 7, 
		    4, 0, 3, 
		    3, 7, 4, 
		    4, 5, 1, 
		    1, 0, 4, 
		    3, 2, 6, 
		    6, 7, 3 
		};

		// Vertex Pos, Texture Coords, Vertex indices
		std::vector<int> layout = { 3, 2, 4 };
		Mesh mesh(vertices, indices, layout);

		return mesh;
	}

	// Mesh MeshFactory::createSphere(float radius)
	// {
	// }

	// void createMesh(float* vertices, unsigned int* indices)
	// {
	// }

}