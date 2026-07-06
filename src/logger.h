#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <utility>

#include <spdlog/async.h>
#include <spdlog/fmt/fmt.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class Logger {
public:
  static constexpr size_t DEFAULT_QUEUE_SIZE = 32768;

  static Logger &getInstance();

  template <typename... Args>
  void trace(spdlog::format_string_t<Args...> fmt, Args &&...args) {

    if (m_logger) {
      m_logger->trace(fmt, std::forward<Args>(args)...);
    }
  }

  template <typename... Args>
  void info(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    if (m_logger) {
      m_logger->info(fmt, std::forward<Args>(args)...);
    }
  }

  template <typename... Args>
  void debug(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    if (m_logger) {
      m_logger->debug(fmt, std::forward<Args>(args)...);
    }
  }

  template <typename... Args>
  void warn(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    if (m_logger) {
      m_logger->warn(fmt, std::forward<Args>(args)...);
    }
  }

  template <typename... Args>
  void error(spdlog::format_string_t<Args...> fmt, Args &&...args) {
    if (m_logger) {
      m_logger->error(fmt, std::forward<Args>(args)...);
    }
  }

  void configure(const std::string &logFileName = "logs/app",
                 int rotationHour = 12, int rotationMinute = 52,
                 spdlog::level::level_enum consoleLevel = spdlog::level::debug,
                 spdlog::level::level_enum fileLevel = spdlog::level::err,
                 bool async = true, size_t queueSize = DEFAULT_QUEUE_SIZE,
                 size_t workers = 1,
                 spdlog::async_overflow_policy policy =
                     spdlog::async_overflow_policy::overrun_oldest);

  void shutdown();

private:
  Logger();
  ~Logger() = default;

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  std::mutex m_cfgMtx;
  std::shared_ptr<spdlog::logger> m_logger; 
};
