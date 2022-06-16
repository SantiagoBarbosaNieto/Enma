#include <Enma.h>
#include "imgui/imgui.h"

class ExampleLayer : public Enma::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//EM_INFO("ExampleLayer::Update");
		if (Enma::Input::IsKeyPressed(Enma::Key::Space))
			EM_TRACE("Spacebar pressed! :D");
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(Enma::Event& event) override
	{
	} 
};

class Sandbox : public Enma::Application 
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}
};
Enma::Application* Enma::CreateApplication() {
	return new Sandbox();
}