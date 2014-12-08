#include "position.h"

namespace Esther {

Position::Position()
    : offset(0), line(0), column(0) {
}
Position::Position(int offset, int line, int column)
    : offset(offset), line(line), column(column) {
}

Position Position::shifted(int delta) {
    return Position(offset + delta, line, column + delta);
}
}
