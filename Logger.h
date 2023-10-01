#ifndef FZ_LOGGER
#define FZ_LOGGER

#include <ostream>
#include <string>
#include <vector>
#include <cstdio>

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

    static const char *cstr(LevelEnum);
    const char *cstr() const;

    friend std::ostream& operator<<(std::ostream&, const Level&);
private:
    LevelEnum value;
};
std::ostream& operator<<(std::ostream&, const Level&);
std::ostream& operator<<(std::ostream&, const Level::LevelEnum&);

class Logger
{
    struct LogStream
    {
        Level level;
        std::ostream &out;

        template<typename T>
        std::ostream& operator<<(const T& val) {
            return this->out << val;
        }
    };

    std::vector<LogStream> streams;

    Logger();
public:
    static Logger &get();

    void registerStream(std::ostream&, Level);

    void log(Level, std::string);
    void info(std::string);
    void warn(std::string);
    void trace(std::string);
    void debug(std::string);
    void error(std::string);
    void fatal(std::string);
};

class CLogger
{
    struct LogStream
    {
        Level level;
        std::FILE* stream;

        operator std::FILE*();
    };

    std::vector<LogStream> streams;

    CLogger();
public:
    static CLogger &get();

    void registerStream(std::FILE*, Level);

    void log(Level, const char *, ...);
};
}

#endif // !FZ_LOGGER
