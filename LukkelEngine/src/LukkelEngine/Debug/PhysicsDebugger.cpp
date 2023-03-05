#include "LKpch.h"
#include "LukkelEngine/Debug/PhysicsDebugger.h"

#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/VertexBufferLayout.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Core/Application.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "btBulletCollisionCommon.h"
#include <stdio.h> //printf debugging


namespace LukkelEngine {

	PhysicsDebugger::PhysicsDebugger()
		:m_debugMode(0)
	{
	}

	PhysicsDebugger::~PhysicsDebugger()
	{
	}

	void PhysicsDebugger::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		btVector3 result = to - from;
		float alpha = 1.0f;
		glm::vec4 colors = { result.x(), result.y(), result.z(), alpha };
		glm::vec3 p0(from.x(), from.y(), from.z());
		glm::vec3 p1(to.x(), to.y(), to.z());
		Renderer::drawLine(p0, p1, colors);
	}

	void PhysicsDebugger::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
	{
	}


	void PhysicsDebugger::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha)
	{
	}

	void PhysicsDebugger::setDebugMode(int debugMode)
	{
		m_debugMode = debugMode;
	}

	void	PhysicsDebugger::draw3dText(const btVector3& location, const char* textString)
	{
	}

	void PhysicsDebugger::reportErrorWarning(const char* warningString)
	{
		printf("%s\n", warningString);
	}

	void PhysicsDebugger::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
	{
	}

}
