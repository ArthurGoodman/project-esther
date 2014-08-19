#pragma once
#include <common.h>

namespace Esther {

class Parser;

// Global access point to the various runtime stuff.
class Runtime
{
public:
    // External environment.

    // Internal environment.
    static Parser *parser;
    static stack<string> sources; // This is mostly used in error messages to show the line containing errors.
    static string *currentSource;

public:
    static void initialize();
    static void release();

    static void pushSource(const string &source);
    static void popSource();

    // Current source code access point.
    static const string &source();
};

}
