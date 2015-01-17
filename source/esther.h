#pragma once
#include <common.h>

namespace esther {

class Lexer;
class Parser;

// Global access point to the various runtime stuff.
class Esther {
public:
    // External environment.

    // Internal environment.
    static Lexer *lexer;
    static Parser *parser;
    static stack<string> sources; // This is used in error messages to show the line containing errors.

public:
    static void initialize();
    static void release();

    static void initializeRuntime();

    static void pushSource(const string &source);
    static void popSource();

    // Current source code access point.
    static const string &source();
};
}
