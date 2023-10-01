#include "Logger.h"
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace logging;

void loggerTest() {
    Logger logger = Logger::get();

    logger.registerStream(std::cout, Level::INFO);

    std::ofstream file("out.log");
    logger.registerStream(file, Level::ALL);

    logger.info("Hello logger\n");
    logger.log(Level::DEBUG, "Hello file logger\n");
    logger.warn("Warn file logger, because logs ALL\n");
}

void cloggerTest() {
    CLogger logger = CLogger::get();

    logger.registerStream(stdout, Level::INFO);

    std::FILE *file = std::fopen("outc.log", "w");
    logger.registerStream(file, Level::ALL);

    logger.log(Level::INFO, "Hello clogger\n"); 
    logger.log(Level::DEBUG, "Hello file clogger: %d\n", 123);
    logger.log(Level::WARN, "Hello warn clogger\n");
}

int main() {
    loggerTest();
    std::puts("===================================");
    cloggerTest();
    return 0;
}
