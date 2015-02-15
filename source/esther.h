#pragma once
#include "common.h"

class Engine;

class Esther {
    static Esther esther;
    static Engine *engine;

public:
    Esther();
    ~Esther();

    static void run(const string &script);
    static void runFile(const string &fileName);
};
