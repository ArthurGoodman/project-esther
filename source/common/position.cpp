#include "position.h"

Position::Position()
    : offset(0), line(0), column(0), valid(false) {
}
Position::Position(int offset, int line, int column)
    : offset(offset), line(line), column(column), valid(true) {
}

Position Position::shifted(int delta) {
    return Position(offset + delta, line, column + delta);
}

bool Position::isValid() {
    return valid;
}
