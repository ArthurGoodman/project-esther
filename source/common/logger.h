#pragma once
#include "common.h"

#include "debug.h"
#include "utility.h"
#include "io.h"

#if DEBUG

class Logger {
    static string activeLog;

public:
    static void setActiveLog(string log);

    template <class T>
    static void write(string log, T data);

    template <class T>
    static void write(T data);
};

template <class T>
void Logger::write(string log, T data) {
    string fileName = "logs\\" + log + ".log";

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
