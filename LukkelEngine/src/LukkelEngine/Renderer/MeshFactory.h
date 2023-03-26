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

		static Mesh CreateCube(glm::vec3& side);
		static Mesh CreateSphere(float radius);

	private:
		
	};
}
