#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Enma/Events/ApplicationEvent.h"

#include "Window.h"

namespace Enma {

	class ENMA_API Application
	
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	//To be defined in client
	Application* CreateApplication();

}

