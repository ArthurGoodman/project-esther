#include "file.h"

#ifdef __WIN32
#include <windows.h>
#endif

#include <fstream>
#include <iostream>

File::File() {
}

File::File(const std::string &path) {
    setPath(path);
}

bool File::exists() const {
#ifdef __WIN32
    DWORD fileAttributes = GetFileAttributesA(path.c_str());
    return fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY);
#endif
    return false;
}

std::string File::getPath() const {
    return path;
}

void File::setPath(const std::string &path) {
#ifdef __WIN32
    char buffer[MAX_PATH];
    GetFullPathNameA(path.c_str(), MAX_PATH, buffer, 0);
    this->path = buffer;
#endif
}

std::string File::getDirectoryPath() const {
    std::size_t i = path.find_last_of("/\\");
    return path.substr(0, i);
}

std::string File::getName() const {
    std::size_t i = path.find_last_of("/\\");
    return path.substr(i + 1, path.size());
}

std::string File::read() const {
    try {
        std::ifstream file(path);
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    } catch (const std::ifstream::failure &e) {
        std::cerr << "error opening file '" << path << "'\n";
        return "";
    }
}
