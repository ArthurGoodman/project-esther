#pragma once

#include <string>

class Position;

class Source {
    const static int maxQuoteLength = 150;

    std::string source;

public:
    Source(const std::string &source);

    const std::string &getSource() const;

    std::string quote(Position pos) const;
};
