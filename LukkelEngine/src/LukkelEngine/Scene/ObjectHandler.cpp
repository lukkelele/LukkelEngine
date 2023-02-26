#include "LKpch.h"
#include "LukkelEngine/Scene/ObjectHandler.h"


namespace LukkelEngine {

	/**
	 * @brief Add a new cube to the scene
	 * @param scene where the cube is to be added
	 * @param name is the desired name of the new cube
	*/
	void ObjectHandler::addCube(Scene& scene, const std::string name)
	{
		Entity entity = scene.createEntity(name);
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
		std::string cubeShaderPath = "assets/shaders/3D/flat.shader";
		std::vector<int> cubeLayout  = { 3, 2, 4 };
		btVector3 dimensions{ 0.5f, 0.5f, 0.5f };
		btVector3 offset{ 0.0f, 10.0f, 0.0f };
		float mass = 1.0f;

		entity.addComponent<MeshComponent>(vertices, indices, cubeShaderPath, cubeLayout, sizeof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
		entity.addComponent<RigidBodyComponent>(dimensions, offset, mass);

		RigidBodyComponent& body = entity.getComponent<RigidBodyComponent>();
		body.bodyType = RigidBodyComponent::BodyType::DYNAMIC;
		body.rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
	}

	void ObjectHandler::addFloor(Scene& scene, const std::string name)
	{
		// 3 vertex positions + 4 floats for color
		std::vector<int> floorLayout = { 3, 4 };
		float yLevel = 0.5f;
		float side = 18.0f;
		float a = 0.99;
		float c = 0.90;
		float floorVertices[7 * 4]  = {
		//   Positions (x,y,z)		Color (GRAY)
		   -side, yLevel, -side,	c, c, c, a,
			side, yLevel, -side,  	c, c, c, a,
		    side, yLevel,  side,	c, c, c, a,
		   -side, yLevel,  side,	c, c, c, a
		};

		unsigned int floorIndices[3 * 2] = {
			0, 1, 2,
			2, 3, 0
		};

		btVector3 dimensions{ a, 0.0f, a };
		btVector3 offset{ 0.0f, -3.0f, 0.0f };
		float mass = 0.0f; // CRUCIAL

		std::string shaderPath = "assets/shaders/3D/default.shader";
		Entity entity = scene.createEntity(name);
		entity.addComponent<MeshComponent>(floorVertices, floorIndices, shaderPath, floorLayout, sizeof(floorVertices) / sizeof(float), sizeof(floorIndices) / sizeof(unsigned int));
		entity.addComponent<RigidBodyComponent>(dimensions, offset, mass);

		MeshComponent& meshComp = entity.getComponent<MeshComponent>();
		RigidBodyComponent& bodyComp = entity.getComponent<RigidBodyComponent>();

		bodyComp.rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
	}

}