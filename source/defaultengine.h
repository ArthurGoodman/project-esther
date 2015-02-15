#pragma once
#include "common.h"

#include "engine.h"

class Lexer;
class Parser;

class DefaultEngine : public Engine {
    Lexer *lexer;
    Parser *parser;

    stack<string> sources; // This is used in error messages to show the line containing errors.

public:
    void run(const string &script);

    void initialize();
    void release();

private:
    void pushSource(const string &source);
    void popSource();

    // Current source code access point.
    const string &source();
};
