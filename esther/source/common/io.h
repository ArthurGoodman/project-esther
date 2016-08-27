#pragma once

#include <map>
#include <string>
#include <memory>

class IO {
    static std::map<std::string, std::unique_ptr<std::fstream>> files;

public:
    static std::string readFile(const std::string &fileName);
    static void writeFile(const std::string &fileName, const std::string &data);

    static void createDirectory(const std::string &name);

    static void openFile(const std::string &fileName);
    static bool isOpen(const std::string &fileName);

    static void writeToFile(const std::string &fileName, const std::string &data);

    static void closeFile(const std::string &fileName);
    static void closeAllFiles();

    static void print(const std::string &data);
    static void printLine(const std::string &data);

    static std::string scan();
    static std::string scanLine();

    static std::string fullPath(const std::string &partialPath);
};