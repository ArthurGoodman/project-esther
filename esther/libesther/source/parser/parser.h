#pragma once

#include "iparser.h"

class Parser : public IParser {
public:
    Expression *parse(const Tokens &tokens);
};
