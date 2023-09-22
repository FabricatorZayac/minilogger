#include "Logger.h"
#include <fstream>
#include <iostream>

using namespace logging;

int main() {
    Logger logger = Logger::get();

    logger.registerStream(std::cout, Level::INFO);

    std::ofstream file("out.log");
    logger.registerStream(file, Level::ALL);

    logger.info("Hello logger\n");
    logger.log(Level::DEBUG, "Hello file logger\n");
    logger.warn("Warn file logger, because logs ALL\n");

    return 0;
}
