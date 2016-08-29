#include "iparser.h"
#include "parser.h"

IParser *IParser::instance() {
    static Parser parser;
    return &parser;
}

IParser::~IParser() {
}
