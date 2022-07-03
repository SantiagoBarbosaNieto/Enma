#pragma once
#include "Enma/Core/Core.h"


#include "Enma/Core/Window.h"
#include "Enma/Core/LayerStack.h"
#include "Enma/Events/Event.h"
#include "Enma/Events/ApplicationEvent.h"

#include "Enma/ImGui/ImGuiLayer.h"


namespace Enma {

	class Application
	
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		bool m_Minimized;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();

}

