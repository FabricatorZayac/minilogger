#ifndef FZ_LOGGER
#define FZ_LOGGER

#include <ostream>
#include <string>
#include <vector>

namespace logging
{
class Level
{
public:
    enum LevelEnum
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        OFF,
        ALL,
    };

    Level(LevelEnum);

    bool operator==(LevelEnum) const;
    bool operator==(const Level&) const;

    friend std::ostream& operator<<(std::ostream&, const Level&);
private:
    LevelEnum value;
};
std::ostream& operator<<(std::ostream&, const Level&);
std::ostream& operator<<(std::ostream&, const Level::LevelEnum&);

class Logger
{
public:
    struct LogStream
    {
        Level level;
        std::ostream &out;

        Level getLevel();
        template<typename T>
        std::ostream& operator<<(const T& val) {
            return this->out << val;
        }
    };

    static Logger &get();

    void registerStream(std::ostream&, Level);

    void log(Level, std::string);
    void info(std::string);
    void warn(std::string);
    void trace(std::string);
    void debug(std::string);
    void error(std::string);
    void fatal(std::string);
private:
    Logger();

    std::vector<LogStream> streams;
};
}

#endif // !FZ_LOGGER
