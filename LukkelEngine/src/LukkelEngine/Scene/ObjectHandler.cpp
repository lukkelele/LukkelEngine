#include "LKpch.h"
#include "LukkelEngine/Scene/ObjectHandler.h"


namespace LukkelEngine {

	void ObjectHandler::addCube(Scene& scene, const std::string name)
	{
		Entity entity = scene.createEntity(name);
		float vertices[8 * 8] = {
			// Positions (x,y,z)  Texture coords     Color
			-0.5f, -0.5f,  0.5f,    0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,    0.2f, 0.5f, 0.0f,
			-0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    0.3f, 0.5f, 0.0f,
			-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 0.5f, 0.5f,
			-0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    0.7f, 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,    0.0f, 0.0f,    1.0f, 0.5f, 0.0f
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
		std::string cubeShaderPath = "assets/shaders/3D/flat.shader";
		std::vector<int> cubeLayout  = { 3, 2, 3 };
		std::vector<int> floorLayout = { 3, 3 };
		entity.addComponent<MeshComponent>(vertices, indices, cubeShaderPath, cubeLayout, sizeof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
		LKLOG_INFO("Cube name: {0}", entity.getName());
		btVector3 dimensions{ 1.0f, 1.0f, 1.0f };
		btVector3 offset{ 0.0f, 30.0f, 0.0f };
		float mass = 2.0f;
		entity.addComponent<RigidBody3DComponent>(dimensions, offset, mass);
		RigidBody3DComponent& body = entity.getComponent<RigidBody3DComponent>();
	}

	void ObjectHandler::addFloor(Scene& scene, const std::string name)
	{
		std::vector<int> floorLayout = { 3, 3 };
		float yLevel = 0.5f;
		float a = 20.0f;

		float floorVertices[6 * 4]  = {
		//   Positions (x,y,z)		Color
		   -a, yLevel,-a,		 1.0f, 1.0f, 1.0f,
			a, yLevel,-a,  		 1.0f, 1.0f, 1.0f,
		    a, yLevel, a,		 1.0f, 1.0f, 1.0f,
		   -a, yLevel, a,		 1.0f, 1.0f, 1.0f
		};

		unsigned int floorIndices[3 * 3] = {
			0, 1, 2,
			2, 1, 3,
			3, 0, 1
		};

		btVector3 dimensions{ a, 0.0f, a };
		// This offset is bugged with the matrix transformations for bullet/opengl vertices
		btVector3 offset{ 0.0f, 0.0f, 0.0f };
		float mass = 0.0f; // CRUCIAL

		std::string shaderPath = "assets/shaders/3D/default.shader";
		Entity entity = scene.createEntity(name);
		entity.addComponent<MeshComponent>(floorVertices, floorIndices, shaderPath, floorLayout, sizeof(floorVertices) / sizeof(float), sizeof(floorIndices) / sizeof(unsigned int));
		entity.addComponent<RigidBody3DComponent>(dimensions, offset, mass);
		RigidBody3DComponent& bodyComp = entity.getComponent<RigidBody3DComponent>();
		bodyComp.rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
	}

}