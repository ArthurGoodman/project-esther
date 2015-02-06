#include "esther.h"

#include "lexer.h"
#include "parser.h"
#include "expression.h"
#include "runtime.h"
#include "io.h"
#include "errorexception.h"

namespace esther {

Esther Esther::esther;

Lexer *Esther::lexer;
Parser *Esther::parser;

stack<string> Esther::sources;

Esther::Esther() {
    initialize();
}

Esther::~Esther() {
    release();
}

void Esther::run(const string &script) {
    pushSource(script);

    try {
        Expression *e = parser->parse(lexer->lex(script));
        IO::printLine("\n=> " + e->eval(Runtime::getRoot())->toString());
        delete e;
    } catch (ErrorException *e) {
        IO::printLine(e->msg());
        delete e;
    } catch (...) {
        IO::printLine("something bad happened...");
    }

    popSource();
}

void Esther::initialize() {
    lexer = Lexer::create();
    parser = Parser::create();

    Expression::initialize();
    Runtime::initialize();
}

void Esther::release() {
    delete lexer;
    delete parser;

    Expression::release();
    Runtime::release();
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
