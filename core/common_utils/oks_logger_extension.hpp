#ifndef COMMON_UTIL_OKS_LOGGER_EXTENSION_HPP
#define COMMON_UTIL_OKS_LOGGER_EXTENSION_HPP

// ===== C/CXX STANDARD LIBRARY =====

// ===== THIRD LIBRARY =====
#include <functional>
#ifdef __cplusplus
extern "C" {
#endif

#include <syslog.h>

#ifdef __cplusplus
}
#endif

#include "common_utils/oks_typedef.hpp"
// ===== SELF LIBRARY =====
#include <common_utils/oks_logger.hpp>

namespace oks {

namespace logger {

struct SyslogConsole : public Singleton<SyslogConsole> {
  using Base = Singleton<SyslogConsole>;
  friend class Singleton<SyslogConsole>;

  static inline int GetLevel(Level level) {
    switch (level) {
      case Level::kDebug: {
        return LOG_DEBUG;
      }
      case Level::kInfo: {
        return LOG_INFO;
      }
      case Level::kWarn: {
        return LOG_WARNING;
      }
      case Level::kError: {
        return LOG_ERR;
      }
      case Level::kFatal: {
        return LOG_CRIT;
      }
      default: {
        return LOG_INFO;
      }
    }
  }

  void log(Level level, const char *msg) {
    syslog(GetLevel(level), "%s", msg);
  }

  static void Register(const char *name, Level level, int facility = LOG_LOCAL0) {
    openlog(name, LOG_USER, facility);
    auto    instance = Instance();
    Console console  = {
      .m_level = level,
      .m_func  = std::bind(&SyslogConsole::log, instance, std::placeholders::_1, std::placeholders::_2),
    };
    Logger::Instance()->add_console(console);
  }
};

}  // namespace logger
}  // namespace oks

#endif  // COMMON_UTIL_OKS_LOGGER_EXTENSION_HPP
