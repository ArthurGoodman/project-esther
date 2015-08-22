#include "tuple.h"

#include "outofrangeexception.h"

Tuple::Tuple(int size)
    : Object("Tuple"), n(size), data(new Object *[n]) {
}

Tuple::Tuple(list<Object *> data)
    : Object("Tuple"), n(data.size()), data(new Object *[n]) {
    foreach (i, data)
        this->data[distance(data.begin(), i)] = *i;
}

Tuple::~Tuple() {
    delete[] data;
}

int Tuple::size() const {
    return n;
}

bool Tuple::isEmpty() const {
    return !n;
}

Object *&Tuple::at(int i) const {
    if (i < 0 || i >= n)
        throw new OutOfRangeException;

    return data[i];
}

Tuple::iterator Tuple::begin() {
    return data;
}

Tuple::const_iterator Tuple::begin() const {
    return data;
}

Tuple::iterator Tuple::end() {
    return data + n;
}

Tuple::const_iterator Tuple::end() const {
    return data + n;
}
