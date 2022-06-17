#pragma once
#include "Core.h"
#include "Window.h"
#include "Enma/LayerStack.h"
#include "Events/Event.h"
#include "Enma/Events/ApplicationEvent.h"
#include "Enma/Renderer/Shader.h"

#include "Enma/ImGui/ImGuiLayer.h"


namespace Enma {

	class ENMA_API Application
	
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();

}

