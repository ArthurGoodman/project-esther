#pragma once
#include "common.h"

namespace esther {
class Engine;
}

class Esther {
    static Esther esther;
    static esther::Engine *engine;

public:
    Esther();
    ~Esther();

    static void run(const string &script);
};
