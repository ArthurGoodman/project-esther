#pragma once

#include "common/token.h"

class Expression;
class Esther;

class IParser {
public:
    static IParser *instance();

    virtual ~IParser();
    virtual Expression *parse(Esther *esther, Tokens &tokens) = 0;
};
