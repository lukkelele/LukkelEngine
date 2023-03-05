#include "LKpch.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include "LukkelEngine/Renderer/Mesh.h"

#include "imgui/examples/imgui_impl_glfw.h"
#include "imgui/examples/imgui_impl_opengl3.h"

namespace LukkelEngine {

	LK_DRAW_MODE Renderer::s_DrawMode;
	float c = 150.0f; // Color

	void Renderer::clear() const
	{
		glClearColor(float(c/255.0f), float(c/255.0f), float(c/255.0f), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.bind();
		va.bind();
		ib.bind();
		glDrawElements(s_DrawMode, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::draw(Mesh& mesh) const
	{
		mesh.bind();
		unsigned int count = mesh.getIndexBuffer()->getCount();
		glDrawElements(s_DrawMode, count, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::renderImGui() const
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	// Remove me
	void Renderer::drawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.bind();
		va.bind();
		ib.bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.bind();
		va.bind();
		ib.bind();
		glDrawElements(GL_LINES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawIndexed(const s_ptr<VertexArray>& va)
	{
		va->bind();
		unsigned int count = va->getIndexBuffer()->getCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color)
	{
		float Line[] = {
			p0.x, p0.y, p0.z,
			p1.x, p1.y, p1.z
		};
		unsigned int indices[] = { 0, 1 };

		VertexArray va;
		VertexBuffer vb(Line, 6 * sizeof(float));
		IndexBuffer ib(indices, 2 * sizeof(unsigned int));
		// Shader shader("assets/shaders/3D/line.shader");

		VertexBufferLayout layout;
		layout.push<float>(3);
		va.addBuffer(vb, layout);

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::mat4& viewProj, const glm::vec4& color)
	{
		float Line[] = {
			p0.x, p0.y, p0.z,
			p1.x, p1.y, p1.z
		};
		unsigned int indices[] = { 0, 1 };

		VertexArray va;
		VertexBuffer vb(Line, 6 * sizeof(float));
		IndexBuffer ib(indices, 2 * sizeof(unsigned int));
		Shader shader("assets/shaders/3D/line.shader");

		VertexBufferLayout layout;
		layout.push<float>(3);
		va.addBuffer(vb, layout);

		shader.bind();
		va.bind();
		ib.bind();
		shader.setUniformMat4f("u_Model", glm::mat4(1.0f));
		shader.setUniformMat4f("u_ViewProj", viewProj);
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawBox(btVector3& halfSize)
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
		Shader shader("assets/shaders/3D/proj.shader");

		VertexBufferLayout layout;
		layout.push<float>(3);
		va.addBuffer(vb, layout);

		glDrawElements(GL_LINES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	// void Renderer::drawShape(btCollisionShape* shape, btVector3& color)
	void Renderer::drawShape(Mesh& mesh, btVector3& color)
	{
		auto body = mesh.getRigidBody();
		auto shape = body->getCollisionShape();
		auto shapeType = mesh.getShapeType();
		// Box 
		if (shapeType == BOX_SHAPE_PROXYTYPE)
		{
			const btBoxShape* box = static_cast<const btBoxShape*>(shape);
			btVector3 halfSize = box->getHalfExtentsWithMargin();
			drawBox(halfSize);
		}
	}


	void Renderer::onWindowResize(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::setDrawMode(LK_DRAW_MODE drawMode)
	{
		s_DrawMode = drawMode;
	}

}
