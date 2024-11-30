#pragma once

#include <core/StringView.hpp>
#include <core/Enum.hpp>


/// A message severity level
template<class LoggerLevel>
class LoggerLevelValues {
public:
    static constexpr LoggerLevel TRACE{0}; // Stack Trace
    static constexpr LoggerLevel DEBUG{1}; // Debug Info
    static constexpr LoggerLevel INFO{2}; // Standard Output
    static constexpr LoggerLevel WARN{3}; // Recoverable Local Error
    static constexpr LoggerLevel ERROR{4}; // Unrecoverable Local Error
    static constexpr LoggerLevel FATAL{5}; // Unrecoverable Error
    static constexpr LoggerLevel BUG{6}; // Program Bug
    static constexpr LoggerLevel NONE{7}; // Don't print anything!
};


class LoggerLevel : public Enum<u8>, public LoggerLevelValues<LoggerLevel> {
private:
    static
    constexpr
    const StringView _names[8] {
        "trace",
        "debug",
        "info",
        "warn",
        "error",
        "fatal",
        "bug",
        "none",
    };
public:


    constexpr
    explicit
    LoggerLevel(u8 id) noexcept : Enum(id) {}


    /// @brief The name of the severity level.
    constexpr
    StringView name() const noexcept {
        return _names[_id];
    }
};
