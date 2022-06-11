#pragma once
#include "Enma.h"

#ifdef EM_PLATFORM_WINDOWS

extern Enma::Application* Enma::CreateApplication();

int main(int argc, char** argv)
{
	Enma::Log::Init();
	EM_CORE_WARN("Initialized log");
	int a = 5;
	EM_INFO("Initialized log Var={0}", a);
	


	printf("Enma Engine started\n");
	auto app = Enma::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Enma only supports Windows!
#endif