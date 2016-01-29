#include "range.h"

#include "function.h"
#include "tuple.h"
#include "integer.h"

Range::Range(int first, int second)
    : Object("Range"), first(first), second(second) {
}

int Range::getFirst() {
    return first;
}

int Range::getSecond() {
    return second;
}

void Range::setFirst(int first) {
    this->first = first;
}

void Range::setSecond(int second) {
    this->second = second;
}

void Range::each(Function *f) {
    for (int i = first; i <= second; i++)
        f->invoke(this, new Tuple({new Integer(i)}));
}

IObject *Range::clone() {
    return new Range(first, second);
}
