#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Custom macro for including file and line info
#define LOG_TRACE(msg, ...) spdlog::trace("[{}:{}] " msg, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) spdlog::debug("[{}:{}] " msg, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_INFO(msg, ...) spdlog::info("[{}:{}] " msg, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_WARN(msg, ...) spdlog::warn("[{}:{}] " msg, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) spdlog::error("[{}:{}] " msg, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_CRITICAL(msg, ...) spdlog::critical("[{}:{}] " msg, __FILE__, __LINE__, ##__VA_ARGS__); exit(1);
