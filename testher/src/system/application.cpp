#include "application.h"

#ifdef __WIN32
#include <windows.h>
#endif

#include "io/file.h"

std::string Application::moduleFilePath() {
#ifdef __WIN32
    char result[MAX_PATH];
    return std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
#endif
    return "";
}

std::string Application::moduleFileName() {
    return File(moduleFilePath()).getName();
}
