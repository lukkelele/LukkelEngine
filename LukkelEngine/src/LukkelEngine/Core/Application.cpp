#include "LKpch.h"
#include "LukkelEngine/Core/Application.h"

namespace LukkelEngine {

	Application* Application::s_Instance;

	Application::Application(const ApplicationDetails& details)
	{
		s_Instance = this;
		Renderer::s_DrawMode = LK_DRAW_TRIANGLES;
		LukkeLog::Init("LukkelEngine.log", "App", "Client");
		LKLOG_TRACE("Starting application");

		WindowProps properties = WindowProps(details.title, details.width, details.height);
		m_Window = Window::Create(properties);
		m_ImGuiLayer = new ImGuiLayer(m_Window->GetWindow());
		m_Window->SetEventCallback(LK_BIND_EVENT_FN(Application::OnEvent));

		m_Timer; // Start the timer
	}

	Application::~Application()
	{
		LKLOG_WARN("Terminating application");
		ImGui::DestroyContext();
	}

	// TODO: Need close event on window to change boolean member
	void Application::Run()
	{
		// while (m_Running)
		while (!glfwWindowShouldClose(m_Window->GetWindow()))
		{
			float deltaTime = m_Timer.getDeltaTime();
			OnUpdate(deltaTime);
		}
	}

	void Application::OnUpdate(float ts)
	{
		m_Renderer->Clear();

		for (auto it = m_LayerStack.rBegin(); it != m_LayerStack.rEnd(); ++it) 
		{
			Layer* currentLayer = *it;
			currentLayer->OnUpdate(ts);
		}

		// Update ImGui
		m_ImGuiLayer->BeginFrame();
		for (auto it = m_LayerStack.rBegin(); it != m_LayerStack.rEnd(); ++it) 
		{
			Layer* currentLayer = *it;
			currentLayer->OnImGuiRender();
		}
		m_ImGuiLayer->EndFrame();

		m_Window->OnUpdate();
	}

	void Application::PushLayer(Layer* layer)
	{
		LKLOG_INFO("Pushing layer -> {0}", layer->GetName());
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		LKLOG_INFO("Pushing overlay -> {0}", layer->GetName());
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PopOverlay(Layer* layer)
	{
		m_LayerStack.PopOverlay(layer);
		layer->OnDetach();
	}

	void Application::OnEvent(Event& e)
	{
	}

	void Application::ResizeWindow(uint16_t width, uint16_t height)
	{
		glViewport(0, 0, width, height);
	}

}
