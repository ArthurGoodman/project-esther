#include "esther.h"

#include "lexer.h"
#include "parser.h"
#include "expression.h"

namespace esther {

Lexer *Esther::lexer;
Parser *Esther::parser;
stack<string> Esther::sources;

void Esther::initialize() {
    lexer = Lexer::create();
    parser = Parser::create();

    Expression::initialize();

    initializeRuntime();
}

void Esther::release() {
    delete lexer;
    delete parser;

    Expression::release();
}

void Esther::initializeRuntime() {
}

void Esther::pushSource(const string &source) {
    sources.push(source);
}

void Esther::popSource() {
    if (!sources.empty())
        sources.pop();
}

const string &Esther::source() {
    return sources.top();
}
}
