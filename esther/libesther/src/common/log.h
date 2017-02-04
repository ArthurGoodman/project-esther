#pragma once

#include <string>

#include "common/config.h"

#ifdef DEBUG

namespace es {

class Log {
public:
    static void write(const std::string &log, const char *fmt, ...);
};
}

#endif
