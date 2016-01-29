#pragma once

#include <list>

#include "object.h"

class Tuple : public Object {
    int n;
    IObject **data;

public:
    typedef IObject **iterator;
    typedef IObject *const *const_iterator;

    Tuple(int size = 0);
    Tuple(const Tuple &other);
    Tuple(std::list<IObject *> data);
    ~Tuple();

    void initialize(std::list<IObject *> data);

    int size() const;
    bool isEmpty() const;

    IObject *&at(int i) const;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    IObject *clone();
};
