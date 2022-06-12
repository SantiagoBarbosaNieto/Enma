#pragma once
#include "Core.h"
#include "Window.h"
#include "Enma/LayerStack.h"
#include "Events/Event.h"
#include "Enma/Events/ApplicationEvent.h"


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
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running;
		LayerStack m_LayerStack;
	};

	//To be defined in client
	Application* CreateApplication();

}

