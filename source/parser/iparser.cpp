#include "iparser.h"

#include "parser.h"

IParser *IParser::parser;

void IParser::initialize() {
    parser = new Parser;
}

void IParser::release() {
    delete parser;
}

IParser *IParser::instance() {
    return parser;
}

IParser::~IParser() {
}
