#include "parser.h"

#include "defaultparser.h"

namespace esther {

Parser *Parser::create() {
    return new DefaultParser;
}

Parser::~Parser() {
}
}
