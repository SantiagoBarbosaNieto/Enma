#include "empch.h"
#include "Application.h"

#include "Enma/Core/Log.h"
#include "Enma/Renderer/Renderer.h"
#include "Enma/Core/Input.h"
#include "Enma/Utils/PlatformUtils.h"

#include <GLFW/glfw3.h>

namespace Enma {


	Application* Application::s_Instance = nullptr;



	Application::Application() 
	{
		EM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(EM_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_Running = true;
		m_Minimized = false;
		
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(EM_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(EM_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			
			if (e.Handled)
				break;
		}
	}


	void Application::Run() {

		while (m_Running)
		{
			float time = Platform::GetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(ts);
			}
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}