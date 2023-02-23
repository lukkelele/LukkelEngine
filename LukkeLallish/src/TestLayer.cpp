#include "TestLayer.h"

#include "LukkelEngine/Core/Application.h"

#include "Entities/Rectangle.h"
#include "Entities/Cube.h"

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

TestLayer::TestLayer()
	: Layer("TestLayer")
{
}

void TestLayer::onAttach()
{

	LukkelEngine::Entity* Cube2 = new LukkelEngine::Cube();
	LukkelEngine::Entity* Cube = new LukkelEngine::Cube();
	Cube2->m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	Cube->m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	// Set the scene to shared pointer
	m_Scene = LukkelEngine::Application::get().getScene();

	btCollisionShape* sphereShape = new btSphereShape(1.0f);
	// Set rotation to 0 and set distance on y axis
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10.0f, 0)));
	btScalar mass = 10.0f;
	btVector3 sphereInertia(0, 0, 0);
	sphereShape->calculateLocalInertia(mass, sphereInertia);
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);
	btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
	sphereRigidBody->setRestitution(1.0f);
	sphereRigidBody->setFriction(1.0f);
	

	btCollisionShape* groundShape = new btBoxShape(btVector3(4.0f, 1.0f, 4.0f)); // Lenght Height Depth
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -2.0f, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f, new btDefaultMotionState(), groundShape, btVector3(0, -10, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	groundRigidBody->setFriction(1.0f);
	groundRigidBody->setRestitution(0.90f);
	groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	Cube->m_RigidBody = sphereRigidBody;
	Cube2->m_RigidBody = groundRigidBody;
	m_Scene->m_WorldPhysics->m_DynamicWorld->addRigidBody(groundRigidBody);
	m_Scene->m_WorldPhysics->m_DynamicWorld->addRigidBody(sphereRigidBody);


	// Add cube to current scene
	LukkelEngine::EntityHandler::addEntity(*Cube);
	LukkelEngine::EntityHandler::addEntity(*Cube2);
}

void TestLayer::onUpdate(float ts)
{			
	m_Scene->onUpdate(1.0f);
	onImGuiRender();
}

void TestLayer::onImGuiRender()
{
}

void TestLayer::onEvent(LukkelEngine::Event& e)
{
}

void TestLayer::onDetach()
{
}
