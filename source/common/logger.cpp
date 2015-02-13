#include "logger.h"

#if DEBUG

string Logger::activeLog;

void Logger::setActiveLog(string log) {
    activeLog = log;
}

#endif
