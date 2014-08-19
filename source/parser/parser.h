#pragma once
#include <common.h>

namespace Esther {

class Expression;

// Syntax analysis.
class Parser
{
public:
    virtual ~Parser();
    virtual Expression *parse() = 0;
};

}
