#pragma once
#include "common.h"

#include "object.h"

class Tuple : public Object {
    typedef Object **iterator;
    typedef Object *const *const_iterator;

    int n;
    Object **data;

public:
    Tuple(int size = 0);
    Tuple(list<Object *> data);
    ~Tuple();

    int size() const;
    bool isEmpty() const;

    Object *&at(int i) const;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;
};
