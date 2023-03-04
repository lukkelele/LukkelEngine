#ifndef GL_DEBUG_DRAWER_H
#define GL_DEBUG_DRAWER_H

#include "LinearMath/btIDebugDraw.h"

#include <vector>
#include <glm/gtc/type_ptr.hpp>

class GLDebugDrawer : public btIDebugDraw
{

	struct Line 
	{
		Line(glm::vec3 a, glm::vec3 b, glm::vec3 color) : a(a), b(b), color(color) {};

		glm::vec3 a;
		glm::vec3 b;
		glm::vec3 color;
	};

    struct Color {
		glm::vec3 color;

        Color(glm::vec3 c) {
            color = c;
        }
    };

	struct LINE {
		glm::vec3 from;
		glm::vec3 to;

		LINE(glm::vec3 start, glm::vec3 end) {
			from = start;
			to = end;
		}
	};


	struct btLine{
		float vertices[6] = {};

		btLine(const btVector3& f, const btVector3& t){
		  vertices[0] = f.x(); vertices[1] = f.y(); vertices[2] = f.z();
		  vertices[3] = t.x(); vertices[4] = t.y(); vertices[5] = t.z(); 
		}
	};



public:

	GLDebugDrawer();
	virtual ~GLDebugDrawer();

	virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	virtual void	drawSphere(const btVector3& p, btScalar radius, const btVector3& color);
	virtual void	drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha);
	virtual void	drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
	virtual void	draw3dText(const btVector3& location, const char* textString);

	virtual void	setDebugMode(int debugMode);
	virtual int		getDebugMode() const { return m_debugMode; }

	virtual void	reportErrorWarning(const char* warningString);

	std::vector<Line>& getLines() { return m_Lines; }

	std::vector<Line> m_Lines;
	std::vector<LINE> LINES;
    std::vector<Color> m_Colors;

    // GLuint vao, vbo[2];

private:
	int m_debugMode;

};

#endif //GL_DEBUG_DRAWER_H