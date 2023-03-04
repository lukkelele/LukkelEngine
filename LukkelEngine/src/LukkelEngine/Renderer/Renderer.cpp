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

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	}


	template<typename T, typename S, typename C>
	void Renderer::drawShape(T&, S, C)
	{
	}
		template<>
		void Renderer::drawShape(btTransform& transform, btCollisionShape* shape, btVector3 color)
		{
		}

	void Renderer::renderImGui() const
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
