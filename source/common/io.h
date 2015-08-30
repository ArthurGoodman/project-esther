#pragma once
#include "common.h"

// Input/Output management.
class IO {
    static map<string, unique_ptr<fstream>> files;

public:
    static string readFile(string fileName);
    static void writeFile(string fileName, string data);

    static void createDirectory(string name);

    static void openFile(string fileName);
    static bool isOpen(string fileName);

    static void writeToFile(string fileName, string data);

    static void closeFile(string fileName);
    static void closeAllFiles();

    static void print(string data);
    static void printLine(string data);

    static string scan();
    static string scanLine();

    static string fullPath(string partialPath);
};
