#include "logger.h"

#include <chrono>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

Logger &Logger::getInstance() {
  static Logger instance;
  return instance;
}

Logger::Logger() = default;

void Logger::configure(const std::string &logFileName, int rotationHour,
                       int rotationMinute,
                       spdlog::level::level_enum consoleLevel,
                       spdlog::level::level_enum fileLevel, bool async,
                       size_t queueSize, size_t workers,
                       spdlog::async_overflow_policy policy) {
  std::lock_guard<std::mutex> lock(m_cfgMtx);

  if(m_logger){
    return;
  }
  
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(consoleLevel);

  fs::path logPath = fs::current_path() / logFileName;

  try {
    if (logPath.has_parent_path()) {
      fs::create_directories(logPath.parent_path());
    }
  } catch (const std::exception &e) {
    spdlog::error("Failed to create log directory: {}", e.what());
  }

  auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
      logPath.string(), rotationHour, rotationMinute, false, 2);
  file_sink->set_level(fileLevel);

  std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

  if (async && !spdlog::thread_pool()) {
    spdlog::init_thread_pool(queueSize, workers);
  }

  auto new_logger =
      (async && spdlog::thread_pool())
          ? std::make_shared<spdlog::async_logger>(
                "app", sinks.begin(), sinks.end(), spdlog::thread_pool(),
                policy)
          : std::make_shared<spdlog::logger>("app", sinks.begin(), sinks.end());

  new_logger->set_level(spdlog::level::trace);
  new_logger->set_pattern("%Y-%m-%d %H:%M:%S.%e [%^%l%$] [tid %t] %v");
  new_logger->flush_on(spdlog::level::err);
  spdlog::flush_every(std::chrono::seconds(2));

  m_logger = std::move(new_logger);
  spdlog::set_default_logger(m_logger);
}

void Logger::shutdown() {
  spdlog::shutdown();
  m_logger.reset();
}
