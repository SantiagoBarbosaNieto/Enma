#pragma once
#include "Enma/Core.h"
#include "Enma/Core/Time.h"


#include "Enma/Window.h"
#include "Enma/LayerStack.h"
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
	
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();

}

