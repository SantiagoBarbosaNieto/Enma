#include "Application.h"

#include "Enma/Events/ApplicationEvent.h"
#include "Enma/Log.h"

namespace Enma {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(EventCategoryApplication))
		{
			EM_TRACE(e);
		}
		else if(e.IsInCategory(EventCategoryInput))
		{
			EM_TRACE(e);
		}

		while (true);
	}
}