#include "LKpch.h"
#include "LukkelEngine/Renderer/Renderer.h"
#include <imgui_impl_glfw_gl3.h> // FIXME

namespace LukkelEngine {

	bool Renderer::s_DrawMode;

	void Renderer::clear() const
	{
		glClearColor(float(51.0f/255.0f), float(98.0f/255.0f), float(125.0f/255.0f), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// FIXME: Delta time
	void Renderer::drawFill(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
		shader.bind();
		va.bind();
		ib.bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	// FIXME: Delta time
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

	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		if (s_DrawMode == LK_DRAW_LINE)
			drawLines(va, ib, shader);
		else
			drawFill(va, ib, shader);
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
}
