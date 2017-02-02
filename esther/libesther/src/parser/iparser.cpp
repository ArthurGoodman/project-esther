#include "iparser.h"

#include "parser/parser.h"

IParser *IParser::instance() {
    static Parser parser;
    return &parser;
}

IParser::~IParser() {
}
