#include "LKpch.h"
#include "LukkelEngine/Scene/Spawner.h"
#include "LukkelEngine/Renderer/Shapes.h"


namespace LukkelEngine {

	Entity& Spawner::createCube(Scene& scene, const std::string& name)
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
		glm::vec3 offset(0.0f, 1.0f, 0.0f);

		Mesh mesh(vertices, indices, cubeShaderPath, cubeLayout, sizeof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
		mesh.createRigidBody(dimensions, offset, mass, RigidBody::Type::DYNAMIC);
		entity.addComponent<Mesh>(mesh); // Has to be last
		return entity;
	}

	void Spawner::createGround(Scene& scene, const std::string& name)
	{
		// 3 vertex positions + 4 floats for color
		Entity entity = scene.createEntity(name);
		std::vector<int> floorLayout = { 3, 4 };
		float yLevel = 0.5f;
		float side = 70.0f;
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

		glm::vec3 dimensions{ side, 0.10f, side };
		glm::vec3 offset{ 0.0f, -10.0f, 0.0f };
		float mass = 0.0f; // CRUCIAL

		std::string floorShaderPath = "assets/shaders/3D/default.shader";
		Mesh mesh(floorVertices, floorIndices, floorShaderPath, floorLayout, sizeof(floorVertices) / sizeof(float), sizeof(floorIndices) / sizeof(unsigned int));
		mesh.createRigidBody(dimensions, offset, mass, RigidBody::Type::STATIC);

		entity.addComponent<Mesh>(mesh); // Has to be last
	}

	void Spawner::addConstraint(Scene& scene, Entity entity)
	{
		auto mesh = entity.getComponent<Mesh>();
		// Get the rigidbody that is to be added a constraint
		btRigidBody* rigidbody = mesh.getRigidBody();
		rigidbody->setActivationState(DISABLE_DEACTIVATION);

		// Create a transform for the pivot point
		btTransform pivot;
		pivot.setIdentity();
	
		// Create our constraint object
		btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(*rigidbody, pivot, true);
		bool bLimitAngularMotion = true;
		if (bLimitAngularMotion) {
			dof6->setAngularLowerLimit(btVector3(0,0,0));
			dof6->setAngularUpperLimit(btVector3(0,0,0));
		}

		auto world = scene.m_World;
		// Add the constraint to the world
		world->addConstraint(dof6, rigidbody);
		// Store a pointer to the constraint
		world->m_PickedConstraint = dof6;
	
		// Define the 'strength'
		float cfm = 0.5f;
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 0);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 1);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 2);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 3);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 4);
		dof6->setParam(BT_CONSTRAINT_STOP_CFM, cfm, 5);
	
		// Define the 'error reduction'
		float erp = 0.5f;
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,0);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,1);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,2);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,3);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,4);
		dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,5);
	}



}