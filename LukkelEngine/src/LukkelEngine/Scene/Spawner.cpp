#include "LKpch.h"
#include "LukkelEngine/Scene/Spawner.h"
#include "LukkelEngine/Renderer/Shapes.h"


namespace LukkelEngine {

	void Spawner::createCube(Scene& scene, const std::string& name)
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
		std::vector<int> cubeLayout  = { 3, 2, 4 }; // 3 vertices, 2 texture coords, 4 color values
		float mass = 3.0f;
		glm::vec3 dimensions(0.5f, 0.5f, 0.5f);
		glm::vec3 offset(0.0f, 5.0f, 0.0f);

		Mesh mesh(vertices, indices, cubeShaderPath, cubeLayout, sizeof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
		mesh.createRigidBody(dimensions, offset);
		mesh.getRigidBody()->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);

		entity.addComponent<Mesh>(mesh); // Has to be last
	}

	void Spawner::createGround(Scene& scene, const std::string& name)
	{
		// 3 vertex positions + 4 floats for color
		Entity entity = scene.createEntity(name);
		std::vector<int> floorLayout = { 3, 4 };
		float yLevel = 0.5f;
		float side = 18.0f;
		float a = 0.00; // Transparent
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

		glm::vec3 dimensions{ side * 10.0f, 1.0f, side };
		glm::vec3 offset{ 0.0f, -3.0f, 0.0f };
		float mass = 0.0f; // CRUCIAL

		std::string floorShaderPath = "assets/shaders/3D/default.shader";
		Mesh groundMesh(floorVertices, floorIndices, floorShaderPath, floorLayout, sizeof(floorVertices) / sizeof(float), sizeof(floorIndices) / sizeof(unsigned int));
		groundMesh.createRigidBody(dimensions, offset, mass);
		auto rigidbody = groundMesh.getRigidBody();
		rigidbody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
		rigidbody->setSleepingThresholds(0.0f, 0.0f);

		entity.addComponent<Mesh>(groundMesh); // Has to be last
	}

	void Spawner::createBarrel(Scene& scene, const std::string& name)
	{
		// 3 vertex positions + 4 floats for color
		Entity entity = scene.createEntity(name);
		std::vector<int> layout = { 3 };

		glm::vec3 dimensions{ 5.0f, 5.0f, 5.0f };
		glm::vec3 offset{ 0.0f, 0.0f, 0.0f };
		float mass = 0.0f; // CRUCIAL


		std::string shader = "assets/shaders/3D/flat.shader";
		Mesh mesh(barrel_vertices, barrel_indices, shader, layout, sizeof(barrel_vertices) / sizeof(float), sizeof(barrel_vertices) / sizeof(unsigned int));
		mesh.createRigidBody(dimensions, offset, mass);
		auto rigidbody = mesh.getRigidBody();
		rigidbody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
		rigidbody->setSleepingThresholds(0.0f, 0.0f);

		entity.addComponent<Mesh>(mesh); // Has to be last
	}

	void Spawner::createPyramid(Scene& scene, const std::string& name)
	{
		Entity entity = scene.createEntity(name);
		std::vector<int> layout = { 3 };
		glm::vec3 dimensions{ 1.0f, 1.0f, 1.0f };
		glm::vec3 offset{ 10.0f, 0.0f, 0.0f };
		float mass = 0.0f; // CRUCIAL

		std::string shader = "assets/shaders/3D/flat.shader";
		Mesh mesh(pyramid_vertices, pyramid_indices, shader, layout, sizeof(pyramid_vertices) / sizeof(float), sizeof(pyramid_indices) / sizeof(unsigned int));
		mesh.createRigidBody(dimensions, offset, mass);
		auto rigidbody = mesh.getRigidBody();
		rigidbody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
		rigidbody->setSleepingThresholds(0.0f, 0.0f);

		entity.addComponent<Mesh>(mesh); // Has to be last
	}



}