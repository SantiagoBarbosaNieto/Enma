#pragma once
#include <memory>

#ifdef EM_PLATFORM_WINDOWS
	#if EM_DYNAMIC_LINKING
		#ifdef EM_BUILD_DLL
			#define ENMA_API __declspec(dllexport)
		#else
			#define ENMA_API __declspec(dllimport)
		#endif
	#else
		#define ENMA_API
	#endif
#else
	#error Enma only supports Windows
#endif

#ifdef EM_ENABLE_ASSERTS
	#define EM_ASSERT(x, ...) { if(!(x)) {EM_ERROR("Assertion failed!: {0}", __VA_ARGS__); __debugbreak();}}
	#define EM_CORE_ASSERT(x, ...) { if(!(x)) {EM_CORE_ERROR("Assertion failed!: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define EM_ASSERT(x,...)
	#define EM_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1 << x)

#define EM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Enma
{
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;
}