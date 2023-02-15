#include "LukkelEngine/Renderer/Renderer.h"
#include <imgui_impl_glfw_gl3.h> // FIXME

namespace LukkelEngine {

	void Renderer::clear() const
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const glm::mat4& transform) const {
		shader.bind();
		va.bind();
		ib.bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const glm::mat4& transform) const {
		shader.bind();
		va.bind();
		ib.bind();
		GLCall(glDrawElements(GL_LINES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::drawImGui() const
	{
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Renderer::onWindowResize(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}
}
