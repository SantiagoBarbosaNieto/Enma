#pragma once
#include "Enma/Core.h"
#include "Enma/Window.h"
#include "Enma/LayerStack.h"
#include "Enma/Events/Event.h"
#include "Enma/Events/ApplicationEvent.h"
#include "Enma/Renderer/Shader.h"
#include "Enma/Renderer/Buffer.h"
#include "Enma/Renderer/VertexArray.h"

#include "Enma/ImGui/ImGuiLayer.h"

#include "Enma/Renderer/OrthographicCamera.h"


namespace Enma {

	class ENMA_API Application
	
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
		bool OnKeyPressed(KeyPressedEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;


		std::shared_ptr<VertexArray> m_SquareVertexArray;
		std::shared_ptr<Shader> m_BlueShader;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();

}

