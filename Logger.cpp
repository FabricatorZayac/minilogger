#include "Logger.h"
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

namespace logging
{
Level::Level(Level::LevelEnum value) :
    value(value) {}

bool Level::operator==(const Level& other) const
{
    return this->value == other.value;   
}
bool Level::operator==(LevelEnum other) const
{
    return this->value == other;   
}
const char *Level::cstr(LevelEnum self)
{
    switch (self)
    {
    case Level::INFO:
        return "INFO";
    case Level::WARN:
        return "WARN";
    case Level::OFF:
        return "OFF";
    case Level::ALL:
        return "ALL";
    case Level::TRACE:
        return "TRACE";
    case Level::DEBUG:
        return "DEBUG";
    case Level::ERROR:
        return "ERROR";
    case Level::FATAL:
        return "FATAL";
    }
}
const char *Level::cstr() const
{
    return Level::cstr(this->value);
}

std::ostream& operator<<(std::ostream& out, const Level::LevelEnum &self)
{
    return out << Level(self).cstr();
}
std::ostream& operator<<(std::ostream& out, const Level &self)
{
    return out << self.cstr();
}

Logger::Logger() { }

Logger& Logger::get()
{
    static Logger instance;
    return instance;
}

void Logger::registerStream(std::ostream& stream, Level level)
{
    this->streams.push_back((Logger::LogStream){ level, stream });
}

void Logger::log(Level level, std::string msg)
{
    for (size_t i = 0; i < this->streams.size(); i++)
    {
        Level streamLevel = streams[i].level;
        if (streamLevel == Level::ALL || streamLevel == level)
        {
            streams[i] << '[' << level << "] " << msg;
        }
    }
}
void Logger::info(std::string msg)
{
    this->log(Level::INFO, msg);
}
void Logger::warn(std::string msg)
{
    this->log(Level::WARN, msg);
}
void Logger::trace(std::string msg)
{
    this->log(Level::TRACE, msg);
}
void Logger::debug(std::string msg)
{
    this->log(Level::DEBUG, msg);
}
void Logger::error(std::string msg)
{
    this->log(Level::ERROR, msg);
}
void Logger::fatal(std::string msg)
{
    this->log(Level::FATAL, msg);
}

CLogger::LogStream::operator FILE*()
{
    return this->stream;
}
CLogger::CLogger() {}
CLogger &CLogger::get()
{
    static CLogger instance;
    return instance;
}
void CLogger::registerStream(std::FILE* stream, Level level)
{
    this->streams.push_back((CLogger::LogStream){ level, stream });
}
void CLogger::log(Level level, const char *fmt, ...)
{
    std::va_list argv;
    va_start(argv, fmt);
    for (size_t i = 0; i < this->streams.size(); i++)
    {
        Level streamLevel = this->streams[i].level;
        if (streamLevel == Level::ALL || streamLevel == level) {
            std::fprintf(this->streams[i], "[%s] ", streamLevel.cstr());
            std::vfprintf(this->streams[i], fmt, argv);
        }
    }
    va_end(argv);
}
}
