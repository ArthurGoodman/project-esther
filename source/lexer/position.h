#pragma once
#include <common.h>

namespace esther {

class Position {
public:
    int offset, line, column;

public:
    Position();
    Position(int offset, int line, int column);

    Position shifted(int delta);
};
}
