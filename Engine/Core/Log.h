#pragma once
#include <memory>
#include <spdlog/spdlog.h>

class Log
{
public:
	static void Init();

	static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

// Core log macros
#define CORE_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
