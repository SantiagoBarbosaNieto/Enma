#include <Enma.h>

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
			EM_INFO("Spacebar pressed! :D");
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
		PushOverlay(new Enma::ImGuiLayer());
	}
	~Sandbox() {

	}
};
Enma::Application* Enma::CreateApplication() {
	return new Sandbox();
}