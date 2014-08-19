#include "defaultparser.h"

#include "defaultlexer.h"

namespace Esther {

DefaultParser::DefaultParser() : lexer(new DefaultLexer) {}
DefaultParser::~DefaultParser() { delete lexer; }

Expression *DefaultParser::parse(const string &source)
{
    lexer->lex(source);

    return 0;
}

}
