#include "common/log.h"

#include <cstdarg>

#include "common/utility.h"
#include "common/io.h"

#if DEBUG

namespace es {

void Log::write(const std::string &log, const char *fmt, ...) {
    std::string fileName = Utility::format("logs/%s.log", log.c_str());

    if (!IO::isOpen(fileName)) {
        IO::createDirectory("logs");
        IO::openFile(fileName);
    }

    va_list ap;
    va_start(ap, fmt);
    IO::writeToFile(fileName, Utility::vformat(fmt, ap));
    va_end(ap);
}
}

#endif
