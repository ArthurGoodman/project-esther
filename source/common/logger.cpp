#include "logger.h"

#if DEBUG

std::string Logger::activeLog;

void Logger::setActiveLog(const std::string &log) {
    activeLog = log;
}

#endif
