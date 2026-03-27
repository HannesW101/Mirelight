#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

// ===================================================================
// Includes
// -------------------------------------------------------------------

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <source_location>
#include <sstream>
#include <string>

// ===================================================================
// Enums
// -------------------------------------------------------------------

enum Log_lvl {

    TRACE    = 1u << 0u,  // Gray         Bits: ...0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 1
    DEBUG    = 1u << 1u,  // Cyan         Bits: ...0 0 0 0 0 0 0 0  0 0 0 0 0 0 1 0
    INFO     = 1u << 2u,  // Green        Bits: ...0 0 0 0 0 0 0 0  0 0 0 0 0 1 0 0
    WARNING  = 1u << 3u,  // Yellow       Bits: ...0 0 0 0 0 0 0 0  0 0 0 0 1 0 0 0
    ERROR    = 1u << 4u,  // Red          Bits: ...0 0 0 0 0 0 0 0  0 0 0 1 0 0 0 0
//  CRITICAL = 1u << 5u,  // Bright red   Bits: ...0 0 0 0 0 0 0 0  0 0 1 0 0 0 0 0
//  SUCCESS  = 1u << 6u,  // Bright green Bits: ...0 0 0 0 0 0 0 0  0 1 0 0 0 0 0 0
//  UPDATE   = 1u << 7u,  // Blue         Bits: ...0 0 0 0 0 0 0 0  1 0 0 0 0 0 0 0
//  FATAL    = 1u << 8u,  // Magenta      Bits: ...0 0 0 0 0 0 0 1  0 0 0 0 0 0 0 0

    ALL_LOG_LVLS = TRACE   | //           Bits: ...0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 1
                   DEBUG   | //           Bits: ...0 0 0 0 0 0 0 0  0 0 0 0 0 0 1 1
                   INFO    | //           Bits: ...0 0 0 0 0 0 0 0  0 0 0 0 0 1 1 1
                   WARNING | //           Bits: ...0 0 0 0 0 0 0 0  0 0 0 0 1 1 1 1
                   ERROR,    //           Bits: ...0 0 0 0 0 0 0 0  0 0 0 1 1 1 1 1
//                 CRITICAL| //           Bits: ...0 0 0 0 0 0 0 0  0 0 1 1 1 1 1 1
//                 SUCCESS | //           Bits: ...0 0 0 0 0 0 0 0  0 1 1 1 1 1 1 1
//                 UPDATE  | //           Bits: ...0 0 0 0 0 0 0 0  1 1 1 1 1 1 1 1
//                 FATAL,    //           Bits: ...0 0 0 0 0 0 0 1  1 1 1 1 1 1 1 1

    NO_LOG_LVLS = 0u         //           Bits: ...0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0
};

// ===================================================================
// logging settings
// -------------------------------------------------------------------

int              const ENABLED_LOG_LVLS       = ALL_LOG_LVLS;
std::string_view const LOG_SPECIFIC_FILE_ONLY = "ALL";

// ===================================================================
// class Logger
// -------------------------------------------------------------------

class Logger final {

public:
    Logger(Log_lvl const level, std::source_location const loc)
        : _level   (level)
        , _location(loc  )
    {}

    ~Logger() {

        bool const is_buffer_empty = _buffer.str().empty();
        if (is_buffer_empty) {

            // No need to flush since buffer is empty.
        } else {

            _flush();
        }
    }

private:
    Log_lvl               _level;
    std::source_location  _location;
    std::ostringstream    _buffer;
    static std::mutex    s_mutex;

public:
    Logger           (Logger const&) = delete;
    Logger& operator=(Logger const&) = delete;
    Logger           (Logger&&     ) = delete;
    Logger& operator=(Logger&&     ) = delete;

public:
    template<typename Input_type>
    Logger& operator<<(Input_type const& value) {

        // Write this value to the internal buffer for flushing later.
        _buffer << value;

        // Allows chaining << ... << ... << ...etc.
        return *this;
    }

private:
    void _flush() {

        // Lock the mutex so no other Logger objects can log till this is finished.
        // Unlocks automatically when this function is out of scope.
        std::lock_guard<std::mutex> lock(s_mutex);

        // Only flush if the log level is enabled right now.
        if (_is_log_lvl_enabled(_level)) {

            // Only show logs for allowed files.
            if (_is_file_allowed()) {

                char const* const reset_color = "\033[0m"; // Reset color

                // Output the buffer log to the console.
                std::cout << _get_color()   << /*---------------------*/     '\n'
                          << '['            << _level_to_str(_level)     << "]\n"
                          << "[Time: "      << _curr_time()              << "]\n"
                          << "[File: "      << _get_file()               << "]\n"
                          << "[Line: "      << _location.line()          << "]\n"
                          << "[Function: "  << _location.function_name() << "]\n"
                          << "[Logger: "       << _buffer.str()             << "]\n"
                          << reset_color    << std::endl;

                // Reset the buffer (not really needed since object gets deleted).
                _buffer.str("");
                _buffer.clear();
            }
        }
    }

    const char* _get_color() const {

        switch (_level) {

        case Log_lvl::TRACE:    return "\033[90m"; // Gray
        case Log_lvl::DEBUG:    return "\033[36m"; // Cyan
        case Log_lvl::INFO:     return "\033[32m"; // Green
        case Log_lvl::WARNING:  return "\033[33m"; // Yellow
        case Log_lvl::ERROR:    return "\033[31m"; // Red
//      case Log_lvl::CRITICAL: return "\033[91m"; // Bright red
//      case Log_lvl::SUCCESS:  return "\033[92m"; // Bright green
//      case Log_lvl::UPDATE:   return "\033[34m"; // Blue
//      case Log_lvl::FATAL:    return "\033[35m"; // Magenta

        default:                return "\033[0m";  // Reset color
        }
    }

    std::string _get_file() const {

        std::string const full_filepath = _location.file_name();

        // Find the last slash (handles both Windows and Unix paths)
        size_t last_slash = full_filepath.find_last_of("/\\");

        // If no slash found, use the entire path as filename
        if (last_slash == std::string::npos) {

            last_slash = 0u;
        } else {

            // Move past the slash
            ++last_slash;
        }

        std::string const file = full_filepath.substr(last_slash);

        return file;
    }

    const char* _level_to_str(Log_lvl const level) const {

        switch (level) {

        case Log_lvl::TRACE:    return "TRACE";
        case Log_lvl::DEBUG:    return "DEBUG";
        case Log_lvl::INFO:     return "INFO";
        case Log_lvl::WARNING:  return "WARNING";
        case Log_lvl::ERROR:    return "ERROR";
//      case Log_lvl::CRITICAL: return "CRITICAL";
//      case Log_lvl::SUCCESS:  return "SUCCESS";
//      case Log_lvl::UPDATE:   return "UPDATE";
//      case Log_lvl::FATAL:    return "FATAL";

        default:                return "UNDEFINED";
        }
    }

    std::string _curr_time() const {

        auto const time_point_now  = std::chrono::system_clock::now();
        auto const time_now        = std::chrono::system_clock::to_time_t(time_point_now);
        std::ostringstream time_stream{};

        // If we are using windows then use the non standard windows safer localtime_s function.
        #ifdef _WIN32

            std::tm tm_info;
            localtime_s(&tm_info, &time_now);
            time_stream << std::put_time(&tm_info, "%H:%M:%S");

        // Otherwise use the standard localtime function.
        #else

            time_stream << std::put_time(std::localtime(&time_now), "%H:%M:%S");
        #endif

        return time_stream.str();
    }

    bool _is_log_lvl_enabled(Log_lvl const log_lvl) const {

        bool const is_enabled = (ENABLED_LOG_LVLS & log_lvl) == log_lvl;
        return     is_enabled;
    }

    bool _is_file_allowed() const {

        std::string const file            = _get_file();
        bool              is_file_allowed = true;

        if (LOG_SPECIFIC_FILE_ONLY == "ALL") {

            is_file_allowed = true;
        } else {

            is_file_allowed = (file == LOG_SPECIFIC_FILE_ONLY);
        }

        return is_file_allowed;
    }

};

// ===================================================================
// Macros
// -------------------------------------------------------------------

#define LOG(level) Logger(level, std::source_location::current())

// ===================================================================
// Definitions for static members
// -------------------------------------------------------------------

inline std::mutex Logger::s_mutex;

#endif // UTILS_LOGGER_H
