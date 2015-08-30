#include "defaultengine.h"

#include "lexer.h"
#include "parser.h"
#include "expression.h"
#include "runtime.h"
#include "io.h"
#include "errorexception.h"
#include "returnexception.h"
#include "breakexception.h"
#include "continueexception.h"
#include "utility.h"

Object *DefaultEngine::run(const string &script, Context *context) {
    if (!context)
        context = Runtime::getRoot();

    Object *value = 0;

    string src = Utility::expandTabs(script);

    pushSource(src);

    try {
        Expression *e = Parser::instance()->parse(Lexer::instance()->lex(src));
        value = e->eval(context);
        delete e;
    } catch (ReturnException *e) {
        IO::printLine("runtime error: return not within a function");
        delete e;
    } catch (BreakException *e) {
        IO::printLine("runtime error: break not within a loop");
        delete e;
    } catch (ContinueException *e) {
        IO::printLine("runtime error: continue not within a loop");
        delete e;
    } catch (ErrorException *e) {
        IO::printLine(fileName() + ":" + e->position().toString() + ": " + e->message());
        IO::printLine(source().quote(e->position()));
        delete e;
    } catch (Exception *e) {
        IO::printLine("error: " + e->message());
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
    pushFileName(IO::fullPath(fileName));

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
    sources.push(Source(source));
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

const Source &DefaultEngine::source() {
    return sources.top();
}

const string &DefaultEngine::fileName() {
    return fileNames.top();
}
