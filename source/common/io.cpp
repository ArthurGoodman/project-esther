#include "io.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>

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
    system(std::string("if not exist logs md " + name).data());
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
    for(auto &i : files)
        i.second->close();

    files.clear();
}

void IO::print(const std::string &data) {
    std::cout << data;
}

void IO::printLine(const std::string &data) {
    std::cout << data << std::endl;
}

std::string IO::scan() {
    std::string str;
    std::cin >> str;
    return str;
}

std::string IO::scanLine() {
    std::string str;
    getline(std::cin, str);
    return str;
}

std::string IO::fullPath(const std::string &partialPath) {
    char path[_MAX_PATH];

    if (_fullpath(path, partialPath.data(), _MAX_PATH))
        return path;

    return "";
}
