#include "tuple.h"

#include "outofrangeexception.h"

Tuple::Tuple(int size)
    : Object("Tuple"), n(size), data(new IObject *[n]) {
}

Tuple::Tuple(const Tuple &other)
    : Object("Tuple"), n(other.size()), data(new IObject *[n]) {
    memcpy(data, other.data, n * sizeof(IObject *));
}

Tuple::Tuple(std::list<IObject *> data)
    : Object("Tuple"), n(data.size()), data(new IObject *[n]) {
    int i = 0;
    for (IObject *o : data)
        this->data[i++] = o;
}

Tuple::~Tuple() {
    delete[] data;
}

void Tuple::initialize(std::list<IObject *> data) {
    if (this->data)
        delete[] this->data;

    n = data.size();
    this->data = new IObject *[n];

    int i = 0;
    for (IObject *o : data)
        this->data[i++] = o;
}

int Tuple::size() const {
    return n;
}

bool Tuple::isEmpty() const {
    return !n;
}

IObject *&Tuple::at(int i) const {
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

IObject *Tuple::clone() {
    return new Tuple(*this);
}
