#include "LKpch.h"
#include "LukkelEngine/Scene/ObjectHandler.h"

// TODO: Clean this up and create functionality to get pointers to the same array
//		 which in turn will decrease memory usage because the current implementation
//		 reinstatiates the same array for each object

namespace LukkelEngine {

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
		std::vector<int> cubeLayout  = { 3, 2, 4 }; // 3 vertices, 2 texture coords, 4 color values
		btVector3 dimensions{ 0.5f, 0.5f, 0.5f };
		btVector3 offset{ 0.0f, 10.0f, 0.0f };
		float mass = 3.0f;

		entity.addComponent<MeshComponent>(vertices, indices, cubeShaderPath, cubeLayout, sizeof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
		entity.addComponent<RigidBodyComponent>(dimensions, offset, mass);
		// entity.addComponent<MaterialComponent>("");

		
		MeshComponent& mesh = entity.getComponent<MeshComponent>();
		// Set offset value to be same as position/origin
		mesh.pos.x = offset.getX(); mesh.pos.y = offset.getY(); mesh.pos.z= offset.getZ();

		RigidBodyComponent& body = entity.getComponent<RigidBodyComponent>();
		body.bodyType = RigidBodyComponent::BodyType::DYNAMIC;
		body.restitution = 0.10f;

		// body.rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT); // This denies gravity setting if no velocity is added
		// Bullet puts slow moving objects to 'sleep' to increase performance.
		// Necessary to tweak the sleep threshold aka the min values for linear and angular velocity
		body.rigidBody->setSleepingThresholds(0.0f, 0.0f);
	}

	void ObjectHandler::addFloor(Scene& scene, const std::string name)
	{
		// 3 vertex positions + 4 floats for color
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

		btVector3 dimensions{ side * 10.0f, 1.0f, side };
		// btVector3 offset{ 0.0f, -3.0f, 0.0f };
		btVector3 offset{ 0.0f, 0.0f, 0.0f };
		float mass = 0.0f; // CRUCIAL

		std::string floorShaderPath = "assets/shaders/3D/default.shader";
		Entity entity = scene.createEntity(name);
		entity.addComponent<MeshComponent>(floorVertices, floorIndices, floorShaderPath, floorLayout,
				sizeof(floorVertices) / sizeof(float), sizeof(floorIndices) / sizeof(unsigned int));
		entity.addComponent<RigidBodyComponent>(dimensions, offset, mass);
		// entity.addComponent<MaterialComponent>("");

		RigidBodyComponent& bodyComp = entity.getComponent<RigidBodyComponent>();

		MeshComponent& mesh = entity.getComponent<MeshComponent>();
		// Set offset value to be same as position/origin
		mesh.pos.x = offset.getX(); mesh.pos.y = offset.getY(); mesh.pos.z= offset.getZ();

		bodyComp.rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
		bodyComp.bodyType = RigidBodyComponent::BodyType::STATIC;
		bodyComp.rigidBody->setSleepingThresholds(0.0f, 0.0f);
	}

}