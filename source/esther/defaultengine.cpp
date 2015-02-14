#include "defaultengine.h"

#include "lexer.h"
#include "parser.h"
#include "expression.h"
#include "runtime.h"
#include "io.h"
#include "errorexception.h"

namespace esther {

void DefaultEngine::run(const string &script) {
    pushSource(script);

    try {
        Expression *e = parser->parse(lexer->lex(script));
        IO::printLine("\n=> " + e->eval(Runtime::getRoot())->toString());
        delete e;
    } catch (Exception *e) {
        IO::printLine(e->message());
        delete e;
    } catch (...) {
        IO::printLine("something bad happened...");
    }

    popSource();
}

void DefaultEngine::initialize() {
    lexer = Lexer::create();
    parser = Parser::create();

    Expression::initialize();
    Runtime::initialize();
}

void DefaultEngine::release() {
    delete lexer;
    delete parser;

    Expression::release();
    Runtime::release();
}

void DefaultEngine::pushSource(const string &source) {
    sources.push(source);
}

void DefaultEngine::popSource() {
    if (!sources.empty())
        sources.pop();
}

const string &DefaultEngine::source() {
    return sources.top();
}
}
