#pragma once

#include "common/token.h"

namespace es {

class Expression;
class Esther;

class IParser {
public:
    static IParser *instance();

    virtual ~IParser();
    virtual Expression *parse(Esther *esther, Tokens &tokens) = 0;
};
}
