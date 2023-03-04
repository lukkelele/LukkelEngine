#include "LKpch.h"
#include "GLDebugDrawer.h"
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
GLDebugDrawer::GLDebugDrawer()
	:m_debugMode(0)
{
}

GLDebugDrawer::~GLDebugDrawer()
{
}

void GLDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
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

void GLDebugDrawer::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
{
}



void GLDebugDrawer::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha)
{
	//	if (m_debugMode > 0)
	{
		const btVector3	n = btCross(b - a, c - a).normalized();
		// glBegin(GL_TRIANGLES);
		// glColor4f(color.getX(), color.getY(), color.getZ(), alpha);
		// glNormal3d(n.getX(), n.getY(), n.getZ());
		// glVertex3d(a.getX(), a.getY(), a.getZ());
		// glVertex3d(b.getX(), b.getY(), b.getZ());
		// glVertex3d(c.getX(), c.getY(), c.getZ());
		// glEnd();
	}
}

void GLDebugDrawer::setDebugMode(int debugMode)
{
	m_debugMode = debugMode;

}

void	GLDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
	// glRasterPos3f(location.x(), location.y(), location.z());
	//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
}

void GLDebugDrawer::reportErrorWarning(const char* warningString)
{
	printf("%s\n", warningString);
}

void GLDebugDrawer::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{

	{
		btVector3 to = pointOnB + normalOnB * 1;//distance;
		const btVector3& from = pointOnB;
		// glColor4f(color.getX(), color.getY(), color.getZ(), 1.f);
		// //glColor4f(0,0,0,1.f);
		// glBegin(GL_LINES);
		// glVertex3d(from.getX(), from.getY(), from.getZ());
		// glVertex3d(to.getX(), to.getY(), to.getZ());
		// glEnd();

		//		glRasterPos3f(from.x(),  from.y(),  from.z());
		//		char buf[12];
		//		sprintf(buf," %d",lifeTime);
				//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
	}

}


