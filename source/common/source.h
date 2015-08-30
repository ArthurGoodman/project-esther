#pragma once
#include "common.h"

class Position;

class Source {
    const static int maxQuoteLength = 150;

    string source;

public:
    Source(const string &source);

    const string &getSource() const;

    string quote(Position pos) const;
};
