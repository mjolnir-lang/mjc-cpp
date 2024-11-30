#pragma once

#include <system/logger/internal/LoggerLevel.hpp>
#include <system/Program.hpp>
#include <container/StringBuffer.hpp>
#include <io/Stream.hpp>
#include <core/Mutex.hpp>


/// A message logger
class Logger {
private:
    StringBuffer _buffer;         // The internal message buffer
    OutputStream<u8> *_stream;    // The standard output stream
    Mutex _mutex;
    LoggerLevel _level;           // The minimum permitted message severity
    LoggerLevel _tmp_level;       // The level to restore when enabled
    bool _has_color;              // The color enable flag
    bool _is_hidden;              // The stream output enable flag
public:


    ///
    /// Constructors
    ///


    /// @brief Create a message logger.
    /// @param level The primary message severity filter level
    /// @param is_hidden If true, the logger will not print to the stream
    /// @param has_color If true, the logger will not print ASCII color sequences
    Logger(
        LoggerLevel level = LoggerLevel::INFO,
        bool is_hidden = false,
        bool has_color = false
    ) :
        _buffer(DEFAULT_BUFFER_SIZE),
        _stream(&Program::STDOUT),
        _level(level),
        _tmp_level(level),
        _has_color(has_color),
        _is_hidden(is_hidden)
    {}


    /// @brief Create a message logger.
    /// @param stream The output stream
    /// @param buffer_size The size of the message buffer
    /// @param level The primary message severity filter level
    /// @param is_hidden If true, the logger will not print to the stream
    /// @param has_color If true, the logger will not print ASCII color sequences
    Logger(
        OutputStream<u8> *stream,
        LoggerLevel level = LoggerLevel::INFO,
        bool is_hidden = false,
        bool has_color = false
    ) :
        _buffer(DEFAULT_BUFFER_SIZE),
        _stream(stream),
        _level(level),
        _tmp_level(level),
        _has_color(has_color),
        _is_hidden(is_hidden)
    {}


    ///
    /// Properties
    ///


    /// @brief 
    String info(bool is_verbose = false) const noexcept;


    /// @brief Set the minimum permitted message severity.
    /// @param level The new message severity level
    LoggerLevel level() const noexcept {
        With<Mutex> lock(_mutex);
        return _level;
    }


    ///
    /// Methods
    ///


    /// @brief Enable the logger.
    void lock() const noexcept {
        _mutex.lock();
    }


    /// @brief Disable the logger.
    void unlock() const noexcept {
        _mutex.unlock();
    }


    /// @brief Enable the logger.
    void enable() noexcept {
        With<Mutex> lock(_mutex);
        _level = _tmp_level;
    }


    /// @brief Disable the logger.
    void disable() noexcept {
        With<Mutex> lock(_mutex);
        _tmp_level = _level;
        _level = LoggerLevel::NONE;
    }


    /// @brief Enable printing to the stream.
    void show() noexcept {
        With<Mutex> lock(_mutex);
        _is_hidden = false;
    }


    /// @brief Disable printing to the stream.
    void hide() noexcept {
        With<Mutex> lock(_mutex);
        _is_hidden = true;
    }


    /// @brief Clear the buffered contents of the logger.
    void clear() noexcept {
        With<Mutex> lock(_mutex);
        _buffer.clear();
    }


    /// @brief Set the minimum permitted message severity.
    /// @param level The new message severity level
    void set_level(LoggerLevel level) noexcept {
        With<Mutex> lock(_mutex);
        _level = level;
    }


    /// @brief Set the minimum permitted message severity.
    /// @param level The new message severity level
    void set_stream(OutputStream<u8> &stream) noexcept {
        With<Mutex> lock(_mutex);
        _stream = &stream;
    }


    /// @brief Print the buffered contents of the logger to the stream.
    /// @param tag The optional tag for filtering messages
    /// @param level The optional message severity for filtering messages
    /// @param max The maximum number of messages to print
    void dump(StringView tag = nullptr, LoggerLevel level = LoggerLevel::TRACE, u32 max = 0) noexcept;


    /// @brief Print a message to the logger identifying a bug in the code.
    /// @param tag The event source tag
    /// @param format The format string
    /// @param args The format string arguments
    template<class... Args>
    void bug(StringView tag, StringView format, Args &&... args) noexcept {
        vmessage(LoggerLevel::BUG, tag, format, {Printable(args)...});
    }


    /// @brief Print a message to the logger describing a system wide unrecoverable error event.
    /// @param tag The event source tag
    /// @param format The format string
    /// @param args The format string arguments
    template<class... Args>
    void fatal(StringView tag, StringView format, Args &&... args) noexcept {
        vmessage(LoggerLevel::FATAL, tag, format, {Printable(args)...});
    }


    /// @brief Print a message to the logger describing a locally unrecoverable error event.
    /// @param tag The event source tag
    /// @param format The format string
    /// @param args The format string arguments
    template<class... Args>
    void error(StringView tag, StringView format, Args &&... args) noexcept {
        vmessage(LoggerLevel::ERROR, tag, format, {Printable(args)...});
    }


    /// @brief Print a message to the logger describing a locally recoverable error event.
    /// @param tag The event source tag
    /// @param format The format string
    /// @param args The format string arguments
    template<class... Args>
    void warn(StringView tag, StringView format, Args &&... args) noexcept {
        vmessage(LoggerLevel::WARN, tag, format, {Printable(args)...});
    }


    /// @brief Print a message to the logger describing normal operation events.
    /// @param tag The event source tag
    /// @param format The format string
    /// @param args The format string arguments
    template<class... Args>
    void info(StringView tag, StringView format, Args &&... args) noexcept {
        vmessage(LoggerLevel::INFO, tag, format, {Printable(args)...});
    }


    /// @brief Print a message to the logger with useful debug information.
    /// @param tag The event source tag
    /// @param format The format string
    /// @param args The format string arguments
    template<class... Args>
    void debug(StringView tag, StringView format, Args &&... args) noexcept {
        vmessage(LoggerLevel::DEBUG, tag, format, {Printable(args)...});
    }


    /// @brief Print a message to the logger describing the flow of execution.
    /// @param tag The event source tag
    /// @param format The format string
    /// @param args The format string arguments
    template<class... Args>
    void trace(StringView tag, StringView format, Args &&... args) noexcept {
        vmessage(LoggerLevel::TRACE, tag, format, {Printable(args)...});
    }


    /// @brief Print a message to the logger.
    /// @param level The message severity
    /// @param tag The event source tag
    /// @param format The format string
    /// @param args The format string arguments
    /// @param size The number of format string arguments
    void vmessage(LoggerLevel level, StringView tag, StringView format, Slice<Printable> args) noexcept;


    ///
    /// Internal
    ///
private:


    /// The maximum length of a format string message.
    static
    constexpr
    u32 MESSAGE_SIZE = 255;


    /// The default buffer size.
    static
    constexpr
    u32 DEFAULT_BUFFER_SIZE = 4096;


public:
    static
    Logger GLOBAL;
};


template<>
class With<Logger> {
private:
    const Logger &_logger;
public:


    constexpr
    With(const Logger &logger) noexcept : _logger(logger) {
        _logger.lock();
    }


    ~With() {
        _logger.unlock();
    }
};


// Default Severity Level
#if !defined(LOGGER_SILENT) && !(defined(LOGGER_TRACE) || defined(LOGGER_DEBUG) || defined(LOGGER_INFO) || defined(LOGGER_WARN) || defined(LOGGER_ERROR) || defined(LOGGER_FATAL) || defined(LOGGER_BUG))
#define LOGGER_INFO
#endif


// Compile Time Macros
#ifdef LOGGER_TRACE
#undef LOGGER_DEBUG
#define LOGGER_DEBUG
#define log_trace(...)  Logger::GLOBAL.trace(nullptr, __VA_ARGS__)
#else
#define log_trace(...)
#endif

#ifdef LOGGER_DEBUG
#undef LOGGER_INFO
#define LOGGER_INFO
#define log_debug(...)  Logger::GLOBAL.debug(nullptr, __VA_ARGS__)
#else
#define log_debug(...)
#endif

#ifdef LOGGER_INFO
#undef LOGGER_WARN
#define LOGGER_WARN
#define log_info(...)  Logger::GLOBAL.info(nullptr, __VA_ARGS__)
#else
#define log_info(...) 
#endif

#ifdef LOGGER_WARN
#undef LOGGER_ERROR
#define LOGGER_ERROR
#define log_warn(...)  Logger::GLOBAL.warn(nullptr, __VA_ARGS__)
#else
#define log_warn(...) 
#endif

#ifdef LOGGER_ERROR
#undef LOGGER_FATAL
#define LOGGER_FATAL
#define log_error(...)  Logger::GLOBAL.error(nullptr, __VA_ARGS__)
#else
#define log_error(...)
#endif

#ifdef LOGGER_FATAL
#undef LOGGER_BUG
#define LOGGER_BUG
#define log_fatal(...)  Logger::GLOBAL.fatal(nullptr, __VA_ARGS__)
#else
#define log_fatal(...)
#endif

#ifdef LOGGER_BUG
#define log_bug(...)  Logger::GLOBAL.bug(nullptr, __VA_ARGS__)
#else
#define log_bug(...)  
#endif


#define lib_trace(tag, ...)  Logger::GLOBAL.trace(tag, __VA_ARGS__)
#define lib_debug(tag, ...)  Logger::GLOBAL.debug(tag, __VA_ARGS__)
#define lib_info(tag, ...)  Logger::GLOBAL.info(tag, __VA_ARGS__)
#define lib_warn(tag, ...)  Logger::GLOBAL.warn(tag, __VA_ARGS__)
#define lib_error(tag, ...)  Logger::GLOBAL.error(tag, __VA_ARGS__)
#define lib_fatal(tag, ...)  Logger::GLOBAL.fatal(tag, __VA_ARGS__)
#define lib_bug(tag, ...)  Logger::GLOBAL.bug(tag, __VA_ARGS__)
