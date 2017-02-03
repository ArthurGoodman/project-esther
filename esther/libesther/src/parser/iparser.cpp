#include "parser/iparser.h"

#include "parser/parser.h"

namespace es {

IParser *IParser::instance() {
    static Parser parser;
    return &parser;
}

IParser::~IParser() {
}
}
