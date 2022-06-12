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
		EM_INFO("ExampleLayer::Update");
	}

	void OnEvent(Enma::Event& event) override
	{
		EM_TRACE("ExampleLayer::Event: {0}", event);
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