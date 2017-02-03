#pragma once

#include <string>

#include "common/config.h"

#if DEBUG

namespace es {

class Log {
public:
    static void write(const std::string &log, const char *fmt, ...);
};
}

#endif
