#include "engine.h"

#include "ilexer.h"
#include "iparser.h"
#include "io.h"
#include "utility.h"
#include "expression.h"
#include "token.h"
#include "context.h"
#include "runtime.h"

Engine::Engine() {
}

Engine::~Engine() {
}

Object *Engine::run(const std::string &script) {
    Object *value = 0;

    std::string src = Utility::expandTabs(script);

    pushSource(src);

    try {
        Context root(&runtime);
        Expression *e = IParser::instance()->parse(ILexer::instance()->lex(src));
        value = e->eval(&root);
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
