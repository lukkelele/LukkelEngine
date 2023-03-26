#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Renderer/Mesh.h"

#include "glad/glad.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

// MOVE
typedef uint8_t LK_DRAW_MODE;
#define LK_DRAW_TRIANGLES  GL_TRIANGLES
#define LK_DRAW_LINES	   GL_LINES
#define LK_DRAW		       LK_DRAW_TRIANGLES // Initial value


namespace LukkelEngine {

	class Entity;

	class Renderer
	{
	public:
		void Clear() const;

		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void Draw(Mesh& mesh) const;
		void DrawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void DrawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void DrawIndexed(const s_ptr<VertexArray>& va);

		// Static because debugging for raycast
		static void DrawLine(const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color = glm::vec4(1.0f));
		void DrawLine(const glm::vec3& p1, const glm::vec3& p2, const glm::mat4& viewProj, const glm::vec4& color = glm::vec4(1.0f));
		void DrawWireframe(Entity& entity, glm::vec4 color) const;

		void DrawCube(btVector3& halfSize);
		void DrawShape(Entity& entity);

		void SetDrawMode(LK_DRAW_MODE drawMode);

		static void OnWindowResize(uint16_t width, uint16_t height);

		static LK_DRAW_MODE s_DrawMode;
		static glm::vec4 s_BackgroundColor;
	};

}
