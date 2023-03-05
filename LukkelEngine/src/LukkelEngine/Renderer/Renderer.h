#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"

#include "imgui/imgui.h"
// #include "GL/glew.h"
#include "glad/glad.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

// MOVE
typedef uint8_t LK_DRAW_MODE;
#define LK_DRAW_TRIANGLES  GL_TRIANGLES
#define LK_DRAW_LINES	   GL_LINES
#define LK_DRAW		       LK_DRAW_TRIANGLES // Initial value


namespace LukkelEngine {

	class Mesh;

	class Renderer
	{
	public:
		void clear() const;

		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void draw(Mesh& mesh) const;
		void drawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void drawIndexed(const s_ptr<VertexArray>& va);

		// Static because debugging for raycast
		static void drawLine(const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color = glm::vec4(1.0f));
		void drawLine(const glm::vec3& p1, const glm::vec3& p2, const glm::mat4& viewProj, const glm::vec4& color = glm::vec4(1.0f));

		void drawBox(btVector3& halfSize);
		void drawShape(btCollisionShape* shape, btVector3& color);
		void drawShape(Mesh& mesh, btVector3& color);

		void renderImGui() const;
		void setDrawMode(LK_DRAW_MODE drawMode);

		static void onWindowResize(uint16_t width, uint16_t height);
		static LK_DRAW_MODE s_DrawMode;
	};

}
