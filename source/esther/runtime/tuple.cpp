#include "tuple.h"

namespace esther {

Tuple::Tuple(int size)
    : n(size), data(new Object *[n]) {
}

Tuple::Tuple(list<Object *> data)
    : n(data.size()), data(new Object *[n]) {
    int c = 0;

    foreach (i, data)
        this->data[c++] = *i;
}

int Tuple::size() const {
    return n;
}

Object *&Tuple::at(int i) const {
    return data[i];
}
}
