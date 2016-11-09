#pragma once

#include "token.h"

class Expression;
class Context;

class IParser {
public:
    static IParser *instance();

    virtual ~IParser();
    virtual Expression *parse(Context *context, Tokens &tokens) = 0;
};
