#pragma once
#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Renderer/Material.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Scene/Scene.h"


namespace LukkelEngine {

	class MeshFactory
	{
	public:
		MeshFactory() = default;
		~MeshFactory() = default;

		static Mesh createBox(glm::vec3& side);
		// static Mesh createMesh(float vertices[], unsigned int indices[]);
		// static Mesh createSphere(float radius);


	};


	// Will implement new system to insert data to Vertex arrays and Vertex buffers
	// static Mesh createMesh(std::vector<Vertex> vertices, std::vector<Index> indices);
}
