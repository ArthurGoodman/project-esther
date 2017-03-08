#include "common/io.h"

#include <climits>
#include <cstdarg>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "common/utility.h"

namespace es {

std::map<std::string, std::unique_ptr<std::fstream>> IO::files;

std::string IO::readFile(const std::string &fileName) {
    std::ifstream file(fileName.data());

    if (!file) {
        std::cout << "error opening file '" << fileName << "'\n";
        return "";
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    file.close();

    return buffer.str();
}

void IO::writeFile(const std::string &fileName, const std::string &data) {
    std::ofstream file(fileName.data());

    if (!file)
        std::cout << "error opening file '" << fileName << "'\n";

    std::ostringstream buffer(data);
    file << buffer.str();

    file.close();
}

void IO::createDirectory(const std::string &name) {
#ifdef __linux
    if (system(std::string("mkdir -p " + name).data()) < 0) {
    }
#elif _WIN32
    system(std::string("if not exist logs md " + name).data());
#endif
}

void IO::openFile(const std::string &fileName) {
    files[fileName] = std::unique_ptr<std::fstream>(new std::fstream(fileName.data(), std::ios::out | std::ios::trunc));
}

bool IO::isOpen(const std::string &fileName) {
    return files.find(fileName) != files.end();
}

void IO::writeToFile(const std::string &fileName, const std::string &data) {
    std::ostringstream buffer(data);
    *files[fileName] << buffer.str();
    files[fileName]->flush();
}

void IO::closeFile(const std::string &fileName) {
    files[fileName]->close();
    files.erase(fileName);
}

void IO::closeAllFiles() {
    for (auto &i : files)
        i.second->close();

    files.clear();
}

void IO::write(const std::string &data) {
    std::cout << data;
}

void IO::write(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    write(Utility::vformat(fmt, ap));
    va_end(ap);
}

void IO::writeLine(const std::string &data) {
    std::cout << data << std::endl;
}

void IO::writeLine(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    writeLine(Utility::vformat(fmt, ap));
    va_end(ap);
}

std::string IO::read() {
    std::string str;
    std::cin >> str;
    return str;
}

std::string IO::readLine() {
    std::string str;
    getline(std::cin, str);
    return str;
}

std::string IO::fullPath(const std::string &partialPath) {
    char path[PATH_MAX];

#ifdef __linux
    if (realpath(partialPath.data(), path))
#elif _WIN32
    if (_fullpath(path, partialPath.data(), PATH_MAX))
#endif
        return path;

    return "";
}
}
