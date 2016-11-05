#pragma once

#include "engine.h"

class Esther {
public:
    static void run(const std::string &script);
    static void runFile(const std::string &fileName);

private:
    static Engine *engine();
};
