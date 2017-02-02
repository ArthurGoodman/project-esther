#pragma once

#include "runtime/esther.h"

class EstherStaticInterface {
public:
    static void run(const std::string &script);
    static void runFile(const std::string &fileName);

private:
    static Esther *esther();
};
