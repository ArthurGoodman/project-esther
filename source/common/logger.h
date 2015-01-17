#pragma once
#include <common.h>

#if DEBUG

class Logger {
    static string activeLog;
    static map<string, string> logs;

public:
    static void setActiveLog(string log);

    template <class T>
    static void write(string log, T data);

    template <class T>
    static void write(T data);

    static void flush();
};

template <class T>
void Logger::write(string log, T data) {
    logs[log] += toString(data);
}

template <class T>
void Logger::write(T data) {
    write(activeLog, data);
}

#endif
