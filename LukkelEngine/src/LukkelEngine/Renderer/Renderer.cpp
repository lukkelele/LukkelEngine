#include "LKpch.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Scene/Entity.h"

namespace LukkelEngine {

	LK_DRAW_MODE Renderer::s_DrawMode;
	glm::vec4 Renderer::s_BackgroundColor = Color::DarkGray;

	void Renderer::Clear() const
	{
		auto c = s_BackgroundColor;
		glClearColor(c.x, c.y, c.z, c.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();
		glDrawElements(s_DrawMode, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Draw(Mesh& mesh) const
	{
		mesh.Bind();
		unsigned int count = mesh.GetIndexBuffer()->GetCount();
		glDrawElements(s_DrawMode, count, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::DrawWireframe(Entity& entity, glm::vec4 color) const
	{
		Mesh& mesh = entity.GetComponent<Mesh>();
		Material& material = entity.GetComponent<Material>();
		mesh.Bind();
		material.Bind();
		auto oldColor = material.GetMaterialColor();
		material.SetMaterialColor(color);
		unsigned int count = mesh.GetIndexBuffer()->GetCount();
		glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, nullptr);
		material.SetMaterialColor(oldColor);
	}

	// Remove me
	void Renderer::DrawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::DrawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();
		glDrawElements(GL_LINES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::DrawIndexed(const s_ptr<VertexArray>& va)
	{
		va->Bind();
		unsigned int count = va->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color)
	{
		float Line[] = {
			p0.x, p0.y, p0.z,
			p1.x, p1.y, p1.z
		};
		unsigned int indices[] = { 0, 1 };

		VertexArray va;
		VertexBuffer vb(Line, 6 * sizeof(float));
		IndexBuffer ib(indices, 2 * sizeof(unsigned int));
		Shader shader("assets/shaders/basic.shader");

		VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
	}

	// FIXME: This is not synced with the rest of the scaling
	void Renderer::DrawCube(btVector3& halfSize)
	{
		// Get the width, height and depth
		float w = halfSize.x(), h = halfSize.y(), d = halfSize.z();
		float vertices[3 * 8] = {
			w,  h,  d,  // 0
		   -w,  h,  d,  // 1
			w, -h,  d,  // 2 
		   -w, -h,  d,  // 3
			w,  h, -d,  // 4
		   -w,  h, -d,  // 5
			w, -h, -d,  // 6
		   -w, -h, -d   // 7
		};

		static unsigned int indices[36] = {
			0, 1, 2,
			3, 2, 1,
			4, 0, 6,
			6, 0, 2,
			5, 1, 4,
			4, 1, 0,
			7, 3, 1,
			7, 1, 5,
			5, 4, 7,
			7, 4, 6,
			7, 2, 3,
			7, 6, 2
		};

		VertexArray va;
		VertexBuffer vb(vertices, 3 * 8 * sizeof(float));
		IndexBuffer ib(indices, 36 * sizeof(unsigned int));
		Shader shader("assets/shaders/basic.shader");
		// Black wireframe
		shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		glDrawElements(GL_LINES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::DrawShape(Entity& entity)
	{
		auto body = entity.GetComponent<Rigidbody>();
		auto shape = body.GetCollisionShape();
		auto shapeType = body.GetShapeType();
		// Box 
		if (shapeType == BOX_SHAPE_PROXYTYPE)
		{
			const btBoxShape* box = static_cast<const btBoxShape*>(shape);
			btVector3 halfSize = box->getHalfExtentsWithMargin();
			DrawCube(halfSize);
		}
	}

	void Renderer::OnWindowResize(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::SetDrawMode(LK_DRAW_MODE drawMode)
	{
		s_DrawMode = drawMode;
	}

}
