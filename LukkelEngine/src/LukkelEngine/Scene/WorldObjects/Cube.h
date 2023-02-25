#pragma once
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Scene/Scene.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"


namespace LukkelEngine {

	namespace WorldObjects  {

		class Cube : public Entity
		{
		public:
			Cube() = default;

			~Cube()
			{
			}

			// void createCube(Scene* scene, const std::string name)
			// {
			// 	auto entity = scene->createEntity(name);
			// 	entity.addComponent<MeshComponent>(vertices, indices, cubeShaderPath, cubeLayout, sizeof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
			// 	LKLOG_INFO("Cube name: {0}", entity.getName());
			// 	entity.addComponent<RigidBody3DComponent>();
			// 	LKLOG_CLIENT_WARN("createCube -> RigidBody3DComponent()");
			// 	auto bodyComp = entity.getComponent<RigidBody3DComponent>();
			// 	btRigidBody* rigidBody = bodyComp.rigidBody;
		 	// 	float xOffset = 0.0f, yOffset = 4.0f, zOffset = 0.0f;
		 	// 	bodyComp.length = 0.5f, bodyComp.height = 0.5f, bodyComp.depth = 0.5f;
			// 	bodyComp.mass = 10.0f;
			// 	bodyComp.friction = 1.0f, bodyComp.restitution = 0.5f;
			// 	bodyComp.inertia = { 0.0f, 0.0f, 0.0f };
		 	// 	btBoxShape* shape = new btBoxShape(btVector3(bodyComp.length, bodyComp.height, bodyComp.depth));
		 	// 	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		 	// 										   btVector3(xOffset, yOffset, zOffset)));
		 	// 	bodyComp.shape->calculateLocalInertia(bodyComp.mass, bodyComp.inertia);
		 	// 	btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(bodyComp.mass, motionState, shape, bodyComp.inertia);
			// 	LKLOG_TRACE("Construct for RigidBody ready! -> BUILDING RIGID BODY");
		 	// 	bodyComp.rigidBody = new btRigidBody(boxBodyConstructionInfo);
		 	// 	bodyComp.rigidBody->setFriction(bodyComp.friction);
		 	// 	bodyComp.rigidBody->setRestitution(bodyComp.restitution);

			// }

			// void createFloor(Scene* scene, const std::string name)
			// {
			// 	auto entity = scene->createEntity(name);
			// 	LKLOG_INFO("Creating FLOOR mesh component");
			// 	entity.addComponent<MeshComponent>(floorVertices, floorIndices, shaderPath, floorLayout, sizeof(floorVertices) / sizeof(float), sizeof(floorIndices) / sizeof(unsigned int));
			// 	LKLOG_INFO("Creating FLOOR rigidbody component");
			// 	entity.addComponent<RigidBody3DComponent>();
			// 	LKLOG_INFO("Floor components created!");
			// 	RigidBody3DComponent& bodyComp = entity.getComponent<RigidBody3DComponent>();
			// 	float mass = 0.0f;
			// 	float xOffset = 0.0f, yOffset = -24.0f, zOffset = 0.0f;
			// 	float length = 4.0f, height = 0.5f, depth = 4.0f;
			// 	float friction = 1.0f, restitution = 0.5f;
			// 	btVector3 inertia{ 0.0f, 0.0f, 0.0f };
			// 	btBoxShape* shape = new btBoxShape(btVector3(length, height, depth));
			// 	btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
			// 										   btVector3(xOffset, yOffset, zOffset)));
			// 	shape->calculateLocalInertia(mass, inertia);
			// 	btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(0.0f, new btDefaultMotionState(), shape, inertia);
			// 	bodyComp.rigidBody = new btRigidBody(boxBodyConstructionInfo);
			// 	bodyComp.rigidBody->setFriction(friction);
			// 	bodyComp.rigidBody->setRestitution(restitution);
			// 	bodyComp.rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
			// 	LKLOG_INFO("Floor created and set to static!");
			// }


		public:
			MeshComponent* mesh;
			RigidBody3DComponent* body;
			std::string shaderPath = "assets/shaders/3D/default.shader";
			std::string cubeShaderPath = "assets/shaders/3D/flat.shader";

			std::vector<int> cubeLayout  = { 3, 2, 3 };
			std::vector<int> floorLayout = { 3, 3 };

			// std::vector<float> vertices = {
			float yLevel = -5.0f;
			float a = 50.0f;

			float floorVertices[6 * 4]  = {
			//   Positions (x,y,z)		Color
				a, yLevel, 0.0f,	 0.0f, 1.0f, 1.0f,
				a, yLevel, a,		 1.0f, 0.0f, 1.0f,
			   -a, yLevel, 0.0f,	 1.0f, 1.0f, 0.0f
			   -a, yLevel, a,		 1.0f, 1.0f, 1.0f
			};

			unsigned int floorIndices[3 * 2] = {
				0, 1, 2,
				0, 2, 3
			};


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

		};

	}

}