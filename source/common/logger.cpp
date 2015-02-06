#include "logger.h"

#include "io.h"

#if DEBUG

string Logger::activeLog;
map<string, string> Logger::logs;

void Logger::setActiveLog(string log) {
    activeLog = log;
}

void Logger::flush() {
    system("if not exist logs md logs");

    foreach (i, logs)
        IO::writeFile("logs\\" + i->first + ".log", i->second);
}

#endif
