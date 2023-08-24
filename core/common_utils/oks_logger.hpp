#ifndef COMMON_UTIL_OKS_LOGGER_HPP
#define COMMON_UTIL_OKS_LOGGER_HPP

// ===== C/CXX STANDARD LIBRARY =====
#include <cstdint>
#include <functional>
#include <list>
#include <sstream>
// ===== THIRD LIBRARY =====
#include <fmt/format.h>
// ===== SELF LIBRARY =====
#include <common_utils/oks_typedef.hpp>

#define OKS_LOG(level) oks::logger::LogProxy(oks::logger::Level::k##level, __FILE__, __LINE__, __func__)
#define OKS_LOG_DEBUG OKS_LOG(Debug)
#define OKS_LOG_INFO OKS_LOG(Info)
#define OKS_LOG_WARN OKS_LOG(Warn)
#define OKS_LOG_ERROR OKS_LOG(Error)
#define OKS_LOG_FATAL OKS_LOG(Fatal)

namespace oks {

namespace logger {

enum class Level : std::uint8_t {
  kDebug,
  kInfo,
  kWarn,
  kError,
  kFatal,
};

using Func = std::function<void(Level level, const char *msg)>;

static inline std::string FmtLevel(Level level) {
  switch (level) {
#define TMP_MACRO(level_)  \
  case Level::k##level_: { \
    return #level_;        \
  }
    TMP_MACRO(Debug)
    TMP_MACRO(Info)
    TMP_MACRO(Warn)
    TMP_MACRO(Error)
    TMP_MACRO(Fatal)
    default: {
      return "Unknown";
    }
#undef TMP_MACRO
  }
}

struct Console {
  Level m_level;
  Func  m_func;
};

class Logger : public Singleton<Logger> {
  using Base = Singleton<Logger>;
  friend class Singleton<Logger>;

 public:
  ~Logger() = default;

 public:
  void add_console(const Console &console) {
    list_console.push_back(console);
  }

  void log(Level level, const char *msg) {
    for (auto &item : list_console) {
      if (item.m_level > level) {
        continue;
      } else {
        item.m_func(level, fmt::format("{}\n", msg).c_str());
      }
    }
  }

 private:
  Logger() = default;
  std::list<Console> list_console;
};

class LogProxy {
 public:
  LogProxy(Level level, const char *file, int line, const char *func)
  : m_level(level)
  , m_file(file)
  , m_line(line)
  , m_func(func) {}

  ~LogProxy() = default;

  void operator()(const char *msg) {
    Logger::Instance()->log(m_level, fmt::format("{}:{} {}[{}]: \"{}\"",
                                                 m_file, m_line, FmtLevel(m_level), m_func, msg)
                                       .c_str());
  }

 private:
  Level       m_level;
  const char *m_file, *m_func;
  int         m_line;
};

}  // namespace logger
}  // namespace oks

#endif  // COMMON_UTIL_OKS_LOGGER_HPP
