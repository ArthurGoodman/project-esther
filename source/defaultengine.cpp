#include "defaultengine.h"

#include "lexer.h"
#include "parser.h"
#include "expression.h"
#include "runtime.h"
#include "io.h"
#include "errorexception.h"
#include "returnexception.h"

Object *DefaultEngine::run(const string &script) {
    return run(script, Runtime::getRoot());
}

Object *DefaultEngine::run(const string &script, Context *context) {
    Object *value = Runtime::getNull();

    pushSource(script);

    try {
        Expression *e = Parser::instance()->parse(Lexer::instance()->lex(script));
        value = e->eval(context);
        delete e;
    } catch (ReturnException *e) {
        IO::printLine("runtime error: return not within a function");
        delete e;
    } catch (Exception *e) {
        IO::printLine(e->message());
        delete e;
    } catch (exception e) {
        IO::printLine((string)"error: " + e.what());
    } catch (...) {
        IO::printLine("something bad happened...");
    }

    popSource();

    return value;
}

void DefaultEngine::initializeEngine() {
    Lexer::initialize();
    Parser::initialize();
    Expression::initialize();
    Runtime::initialize();
}

void DefaultEngine::releaseEngine() {
    Lexer::release();
    Parser::release();
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
