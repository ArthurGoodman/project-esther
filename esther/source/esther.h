#pragma once

#include <string>

#include "engine.h"

class Esther {
    static Engine engine;

public:
    static void run(const std::string &script);
    static void runFile(const std::string &fileName);
};
