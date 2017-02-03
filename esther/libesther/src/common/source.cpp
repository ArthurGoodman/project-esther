#include "common/source.h"

#include <algorithm>

#include "common/position.h"

namespace es {

Source::Source(const std::string &source)
    : source(source) {
}

const std::string &Source::getSource() const {
    return source;
}

std::string Source::quote(Position position) const {
    int start = source.find_last_of('\n', position.getOffset()) + 1;
    int end = source.find_first_of('\n', position.getOffset());

    std::string quote = source.substr(start, end - start);

    int size = quote.size();

    quote = quote.substr(std::max(0, position.getColumn() - maxQuoteLength / 2), maxQuoteLength);

    std::string preffix = position.getColumn() > maxQuoteLength / 2 ? "... " : "";
    std::string suffix = size - position.getColumn() > maxQuoteLength / 2 ? " ..." : "";

    int pos = position.getColumn() > maxQuoteLength / 2 ? maxQuoteLength / 2 : position.getColumn();

    std::string pointer = "";
    pointer.insert(0, pos + preffix.size() - 1, ' ');
    pointer += "^";

    return preffix + quote + suffix + "\n" + pointer;
}
}
