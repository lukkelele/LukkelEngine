#pragma once

#include "LukkelEngine/Renderer/Renderer.h"
#include "LinearMath/btIDebugDraw.h"

#include <vector>
#include <glm/gtc/type_ptr.hpp>

namespace LukkelEngine {

	class PhysicsDebugger : public btIDebugDraw, public Renderer
	{
		struct btLine
		{
			float vertices[6] = {};
			btLine(const btVector3& f, const btVector3& t){
			  vertices[0] = f.x(); vertices[1] = f.y(); vertices[2] = f.z();
			  vertices[3] = t.x(); vertices[4] = t.y(); vertices[5] = t.z(); 
			}
		};

	public:
		PhysicsDebugger();
		virtual ~PhysicsDebugger();
		virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
		virtual void	drawSphere(const btVector3& p, btScalar radius, const btVector3& color);
		virtual void	drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha);
		virtual void	drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
		virtual void	draw3dText(const btVector3& location, const char* textString);
		virtual void	setDebugMode(int debugMode);
		virtual int		getDebugMode() const { return m_DebugMode; }
		virtual void	reportErrorWarning(const char* warningString);

	private:
		int m_DebugMode;
	};

}