#include "parser.h"

#include "defaultparser.h"

Parser *Parser::parser;

void Parser::initialize() {
    parser = new DefaultParser;
}

void Parser::release() {
    delete parser;
}

Parser *Parser::instance() {
    return parser;
}

Parser::~Parser() {
}
