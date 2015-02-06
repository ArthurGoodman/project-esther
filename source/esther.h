#pragma once
#include "common.h"

namespace esther {

class Lexer;
class Parser;

class Esther {
    static Esther esther;

    static Lexer *lexer;
    static Parser *parser;

    static stack<string> sources; // This is used in error messages to show the line containing errors.

public:
    Esther();
    ~Esther();

    static void run(const string &script);

private:
    static void initialize();
    static void release();

    static void pushSource(const string &source);
    static void popSource();

    // Current source code access point.
    static const string &source();
};
}
