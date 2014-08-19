#include "defaultparser.h"

#include "defaultlexer.h"

namespace Esther {

DefaultParser::DefaultParser() : lexer(new DefaultLexer) {}
DefaultParser::~DefaultParser() { delete lexer; }

Expression *DefaultParser::parse()
{
    lexer->lex();

    return 0;
}

}
