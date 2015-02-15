#include "parser.h"

#include "defaultparser.h"

Parser *Parser::create() {
    return new DefaultParser;
}

Parser::~Parser() {
}
