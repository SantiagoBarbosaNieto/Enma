#pragma once
#include "Enma.h"

#ifdef EM_PLATFORM_WINDOWS

extern Enma::Application* Enma::CreateApplication();

int main(int argc, char** argv)
{
	Enma::Log::Init();

	EM_PROFILE_BEGIN_SESSION("Startup", "EnmaProfile-Startup.json");
	auto app = Enma::CreateApplication();
	EM_PROFILE_END_SESSION();
	
	EM_PROFILE_BEGIN_SESSION("Runtime", "EnmaProfile-Runtime.json");
	app->Run();
	EM_PROFILE_END_SESSION();

	EM_PROFILE_BEGIN_SESSION("Shutdown", "EnmaProfile-Shutdown.json");
	delete app;
	EM_PROFILE_END_SESSION();
}

#else
	#error Enma only supports Windows!
#endif