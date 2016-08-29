#pragma once

#include "iparser.h"

class Parser : public IParser {
public:
    Expression *parse(Tokens &tokens);
};
