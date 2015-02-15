#pragma once
#include "common.h"

class Position {
public:
    int offset, line, column;
    bool valid;

public:
    Position();
    Position(int offset, int line, int column);

    Position shifted(int delta);

    bool isValid();
};
