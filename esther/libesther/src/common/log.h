#pragma once

#include <string>

#include "common/config.h"

#if DEBUG

class Log {
public:
    static void write(const std::string &log, const char *fmt, ...);
};

#endif
