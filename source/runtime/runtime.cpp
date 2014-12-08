#include "runtime.h"

namespace Esther {

Parser *Runtime::parser;
stack<string> Runtime::sources;
string *Runtime::currentSource;

void Runtime::initialize() {
}

void Runtime::release() {
}

void Runtime::pushSource(const string &source) {
    sources.push(source);
    currentSource = &sources.top();
}

void Runtime::popSource() {
    sources.pop();
    if (!sources.empty())
        currentSource = &sources.top();
}

const string &Runtime::source() {
    return *currentSource;
}
}
