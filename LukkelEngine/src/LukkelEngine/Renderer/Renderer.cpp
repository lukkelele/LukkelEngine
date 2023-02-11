#ifdef LK_USE_PRECOMPILED_HEADERS
	#include <LKpch.h>
#endif
#include <Renderer.h>
#include <imgui_impl_glfw_gl3.h> // FIXME

namespace LukkelEngine {

	void Renderer::clear() const
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// void Renderer::attachCamera(Camera* cam) { m_Cam = cam; }

	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.bind();
		va.bind();
		ib.bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::drawImGui() const
	{
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Renderer::drawIndexed(const s_ptr<VertexArray> &va, uint32_t indexCount) const
	{
		va->bind();
		uint32_t count = indexCount ? indexCount : va->getIndexBuffer()->getCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}


	void Renderer::onWindowResize(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}
}
