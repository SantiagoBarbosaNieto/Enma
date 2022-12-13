#pragma once

#include "Enma/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Enma {
	class Log
	{
	public: 
		
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

	};

}

//Core log macros
#define EM_CORE_TRACE(...)   Enma::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EM_CORE_INFO(...)    Enma::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EM_CORE_WARN(...)    Enma::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EM_CORE_ERROR(...)   Enma::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EM_CORE_FATAL(...)   Enma::Log::GetCoreLogger()->critical(__VA_ARGS__)


//Normal log macros
#define EM_TRACE(...)        Enma::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EM_INFO(...)         Enma::Log::GetClientLogger()->info(__VA_ARGS__)
#define EM_WARN(...)         Enma::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EM_ERROR(...)        Enma::Log::GetClientLogger()->error(__VA_ARGS__)
#define EM_FATAL(...)        Enma::Log::GetClientLogger()->critical(__VA_ARGS__)
