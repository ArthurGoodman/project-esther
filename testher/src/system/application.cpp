#include "application.h"

#include <windows.h>

#include "io/file.h"

std::string Application::moduleFilePath() {
    char result[MAX_PATH];
    return std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
}

std::string Application::moduleFileName() {
    return File(moduleFilePath()).getName();
}
