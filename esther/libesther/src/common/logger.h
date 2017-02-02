#pragma once

#include "common/common.h"
#include "common/utility.h"
#include "common/io.h"

#if DEBUG

class Logger {
    static std::string activeLog;

public:
    static void setActiveLog(const std::string &log);

    template <class T>
    static void write(const std::string &log, T data);

    template <class T>
    static void write(T data);
};

template <class T>
void Logger::write(const std::string &log, T data) {
    std::string fileName = "logs\\" + log + ".log";

    if (!IO::isOpen(fileName)) {
        IO::createDirectory("logs");
        IO::openFile(fileName);
    }

    IO::writeToFile(fileName, Utility::toString(data));
}

template <class T>
void Logger::write(T data) {
    write(activeLog, data);
}

#endif
