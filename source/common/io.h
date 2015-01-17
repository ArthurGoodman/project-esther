#pragma once
#include <common.h>

// Input/Output management.
class IO {
public:
    static string readFile(string fileName);
    static void writeFile(string fileName, string data);
};
