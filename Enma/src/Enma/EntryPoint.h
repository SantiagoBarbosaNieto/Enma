#pragma once
#include "Enma.h"

#ifdef EM_PLATFORM_WINDOWS

extern Enma::Application* Enma::CreateApplication();

int main(int argc, char** argv)
{
	printf("Enma Engine started\n");
	auto app = Enma::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Enma only supports Windows!
#endif