#include "engine.h"

#include "ilexer.h"
#include "iparser.h"
#include "io.h"
#include "utility.h"
#include "expression.h"
#include "token.h"
#include "context.h"
#include "runtime.h"
#include "errorexception.h"

Engine::Engine() {
    runtime.initialize();
}

Engine::~Engine() {
    runtime.release();
}

Object *Engine::run(const std::string &script) {
    Object *value = 0;

    std::string src = Utility::expandTabs(script);

    pushSource(src);

    try {
        Context root(&runtime);
        Expression *e = IParser::instance()->parse(&root, ILexer::instance()->lex(src));
        value = e->eval(&root);
        delete e;
    } catch (ErrorException *e) {
        IO::printLine(fileName() + ":" + (e->getPosition().isValid() ? e->getPosition().toString() + ": " : " ") + e->message());
        if (e->getPosition().isValid())
            IO::printLine(source().quote(e->getPosition()));
        delete e;
    } catch (Exception *e) {
        IO::printLine(e->message());
        delete e;
    } catch (std::exception e) {
        IO::printLine((std::string) "error: " + e.what());
    } catch (...) {
        IO::printLine("something bad happened...");
    }

    popSource();

    return value;
}

Object *Engine::runFile(const std::string &fileName) {
    pushFileName(IO::fullPath(fileName));

    Object *value = run(IO::readFile(fileName));

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
