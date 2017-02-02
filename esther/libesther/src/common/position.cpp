#include "position.h"

#include "common/utility.h"

Position::Position()
    : offset(0)
    , line(0)
    , column(0)
    , valid(false) {
}
Position::Position(int offset, int line, int column)
    : offset(offset)
    , line(line)
    , column(column)
    , valid(true) {
}

Position Position::shifted(int delta) const {
    return Position(offset + delta, line, column + delta);
}

int Position::getOffset() const {
    return offset;
}

int Position::getLine() const {
    return line;
}

int Position::getColumn() const {
    return column;
}

bool Position::isValid() const {
    return valid;
}

void Position::set(int offset, int line, int column) {
    this->offset = offset;
    this->line = line;
    this->column = column;

    valid = true;
}

std::string Position::toString() const {
    return Utility::toString(line) + ":" + Utility::toString(column);
}
