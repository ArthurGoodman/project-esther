#pragma once
#include "common.h"

#include "object.h"

class Tuple : public Object {
    int n;
    IObject **data;

public:
    typedef IObject **iterator;
    typedef IObject *const *const_iterator;

    Tuple(int size = 0);
    Tuple(const Tuple &other);
    Tuple(list<IObject *> data);
    ~Tuple();

    void initialize(list<IObject *> data);

    int size() const;
    bool isEmpty() const;

    IObject *&at(int i) const;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    IObject *clone();
};
