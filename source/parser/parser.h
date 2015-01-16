#pragma once
#include <common.h>

namespace esther {

class Expression;

// Syntax analysis.
class Parser {
public:
    static Parser *create();

    virtual ~Parser();
    virtual Expression *parse(const string &source) = 0;
};
}
