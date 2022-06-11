#pragma once

#ifdef EM_PLATFORM_WINDOWS
	#ifdef EM_BUILD_DLL
		#define ENMA_API __declspec(dllexport)
	#else
		#define ENMA_API __declspec(dllimport)
	#endif
#else
	#error Enma only supports Windows
#endif

#define BIT(x) (1 << x)