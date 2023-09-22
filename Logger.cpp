#include "Logger.h"
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

std::ostream& operator<<(std::ostream& out, const Level::LevelEnum &self)
{
    switch (self) {
    case Level::INFO:
        return out << "INFO";
    case Level::WARN:
        return out << "WARN";
    case Level::OFF:
        return out << "OFF";
    case Level::ALL:
        return out << "ALL";
    case Level::TRACE:
        return out << "TRACE";
    case Level::DEBUG:
        return out << "DEBUG";
    case Level::ERROR:
        return out << "ERROR";
    case Level::FATAL:
        return out << "FATAL";
    }
}
std::ostream& operator<<(std::ostream& out, const Level &self)
{
    return out << self.value;
}

Logger::Logger() { }

Logger& Logger::get()
{
    static Logger instance;
    return instance;
}

Level Logger::LogStream::getLevel()
{
    return this->level;
}

void Logger::registerStream(std::ostream& stream, Level level)
{
    this->streams.push_back((Logger::LogStream){ level, stream });
}

void Logger::log(Level level, std::string msg)
{
    for (size_t i = 0; i < this->streams.size(); i++) {
        Level streamLevel = streams[i].getLevel();
        if (streamLevel == Level::ALL || streamLevel == level) {
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
}
