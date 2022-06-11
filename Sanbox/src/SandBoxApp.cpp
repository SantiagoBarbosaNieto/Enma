#include <Enma.h>

class Sandbox : public Enma::Application 
{
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};
Enma::Application* Enma::CreateApplication() {
	return new Sandbox();
}