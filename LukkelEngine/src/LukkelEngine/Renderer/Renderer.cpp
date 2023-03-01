#include "LKpch.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include <imgui_impl_glfw_gl3.h> // FIXME

namespace LukkelEngine {

	LK_DRAW_MODE Renderer::s_DrawMode;
	float c = 150.0f; // Color

	void Renderer::clear() const
	{
		// glClearColor(float(51.0f/255.0f), float(98.0f/255.0f), float(125.0f/255.0f), 1.0f); // Light blue
		// glClearColor(float(87.0f/255.0f), float(44.0f/255.0f), float(70.0f/255.0f), 1.0f); // Gray
		glClearColor(float(c/255.0f), float(c/255.0f), float(c/255.0f), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/**
	 * @brief Renders accordingly to the current draw mode (LK_LINES, LK_TRIANGLES etc..)
	 * @param va 
	 * @param ib 
	 * @param shader 
	*/
	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.bind();
		va.bind();
		ib.bind();
		glDrawElements(s_DrawMode, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::drawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
		shader.bind();
		va.bind();
		ib.bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
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

	void Renderer::renderImGui() const
	{
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
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
