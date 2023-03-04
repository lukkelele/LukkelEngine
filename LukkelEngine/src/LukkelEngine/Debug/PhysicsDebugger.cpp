#include "LKpch.h"
#include "LukkelEngine/Debug/PhysicsDebugger.h"
// #include "GLDebugFont.h"
// #include "GL/glew.h"

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


PhysicsDebugger::PhysicsDebugger()
	:m_debugMode(0)
{
}

PhysicsDebugger::~PhysicsDebugger()
{
}

void PhysicsDebugger::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{

	btLine lines(from, to);
	btVector3 result = to - from;
	glm::vec3 colors = { result.x(), result.y(), result.z() };

	GLuint indices[] = { 0, 1 };
	GLuint vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6, lines.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 2, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0); glBindVertexArray(0);

	auto viewProjection = LukkelEngine::Application::get().getCamera()->getViewProjection();
	// LukkelEngine::Shader shader("assets/shaders/3D/line.shader");
	// shader.bind();
	// shader.setUniformMat4f("u_ViewProj", viewProjection);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//delete buffers
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
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


