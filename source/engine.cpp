#include "engine.h"

#include "ilexer.h"
#include "iparser.h"
#include "expression.h"
#include "runtime.h"
#include "io.h"
#include "errorexception.h"
#include "returnexception.h"
#include "breakexception.h"
#include "continueexception.h"
#include "utility.h"

Engine::Engine() {
    Runtime::initialize();
}

Engine::~Engine() {
    Runtime::release();
}

IObject *Engine::run(const std::string &script, Context *context) {
    if (!context)
        context = Runtime::getRoot();

    IObject *value = 0;

    std::string src = Utility::expandTabs(script);

    pushSource(src);

    try {
        Expression *e = IParser::instance()->parse(ILexer::instance()->lex(src));
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
        IO::printLine(fileName() + ":" + (e->getPosition().isValid() ? e->getPosition().toString() + ": " : " ") + e->message());
        if (e->getPosition().isValid())
            IO::printLine(source().quote(e->getPosition()));
        delete e;
    } catch (Exception *e) {
        IO::printLine("error: " + e->message());
        delete e;
    } catch (std::exception e) {
        IO::printLine((std::string) "error: " + e.what());
    } catch (...) {
        IO::printLine("something bad happened...");
    }

    popSource();

    return value;
}

IObject *Engine::runFile(const std::string &fileName, Context *context) {
    pushFileName(IO::fullPath(fileName));

    IObject *value = run(IO::readFile(fileName), context);

    popFileName();

    return value;
}

void Engine::pushSource(const std::string &source) {
    sources.push(Source(source));
}

void Engine::popSource() {
    if (!sources.empty())
        sources.pop();
}

void Engine::pushFileName(const std::string &fileName) {
    fileNames.push(fileName);
}

void Engine::popFileName() {
    if (!fileNames.empty())
        fileNames.pop();
}

const Source &Engine::source() {
    return sources.top();
}

const std::string &Engine::fileName() {
    return fileNames.top();
}
