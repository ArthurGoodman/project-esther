#pragma once
#include <common.h>

namespace Esther {

class Parser;

class Runtime
{
public:
    static Parser *parser;

public:
    static void initialize();
    static void release();
};

}
