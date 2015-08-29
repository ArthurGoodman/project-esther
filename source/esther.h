#pragma once
#include "common.h"

class Engine;

class Esther {
    static Esther esther;

public:
    Esther();
    ~Esther();

    static void runFile(const string &fileName);
};
