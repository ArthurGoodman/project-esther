#pragma once

#include <string>

namespace es {

class Position {
    int offset, line, column;
    bool valid;

public:
    Position();
    Position(int offset, int line, int column);

    Position shifted(int delta) const;

    int getOffset() const;
    int getLine() const;
    int getColumn() const;

    bool isValid() const;

    void set(int offset, int line, int column);

    std::string toString() const;
};
}
