#include "defaultengine.h"

#include "lexer.h"
#include "parser.h"
#include "expression.h"
#include "runtime.h"
#include "io.h"
#include "errorexception.h"
#include "returnexception.h"

Object *DefaultEngine::run(const string &script, Context *context) {
    if (!context)
        context = Runtime::getRoot();

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
        IO::printLine((string) "error: " + e.what());
    } catch (...) {
        IO::printLine("something bad happened...");
    }

    popSource();

    return value;
}

Object *DefaultEngine::runFile(const string &fileName, Context *context) {
    pushFileName(fileName);

    Object *value = run(IO::readFile(fileName), context);

    popFileName();

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

void DefaultEngine::pushFileName(const string &fileName) {
    fileNames.push(fileName);
}

void DefaultEngine::popFileName() {
    if (!fileNames.empty())
        fileNames.pop();
}

const string &DefaultEngine::source() {
    return sources.top();
}
