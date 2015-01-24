#include "class.h"

namespace esther {

Class::Class(string name)
    : name(name) {
}

string Class::getName() {
    return name;
}

string Class::toString() {
    return name;
}
}
