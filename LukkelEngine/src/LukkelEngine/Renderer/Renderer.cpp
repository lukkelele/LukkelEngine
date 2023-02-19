#include "LukkelEngine/Renderer/Renderer.h"
#include <imgui_impl_glfw_gl3.h> // FIXME

namespace LukkelEngine {

	void Renderer::clear() const
	{
		glClearColor(float(51.0f/255.0f), float(98.0f/255.0f), float(125.0f/255.0f), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// FIXME: Delta time
	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
		shader.bind();
		va.bind();
		ib.bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	//void Renderer::draw(Entity& entity)
	//{
	//	auto va = entity.getVertexArray();
	//	auto ib = entity.getIndexBuffer();
	//	auto shader = entity.getShader();
	//	draw(*va, *ib, *shader);
	//}

	//void Renderer::drawLines(Entity& entity)
	//{
	//	auto va = entity.getVertexArray();
	//	auto ib = entity.getIndexBuffer();
	//	auto shader = entity.getShader();
	//	drawLines(*va, *ib, *shader);
	//}

	// FIXME: Delta time
	void Renderer::drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
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
