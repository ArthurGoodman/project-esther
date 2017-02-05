#pragma once

#include "memory/managedobject.h"

namespace es {

template <class T>
class Array : public ManagedObject {
    size_t arraySize;

public:
    typedef T *iterator;

    static Array *create(size_t size);

    ~Array();

    iterator begin();
    iterator end();

    T *data() const;

    T *operator*() const;
    T &operator[](int index) const;

    size_t size() const;

    void mapOnReferences(void (*f)(ManagedObject *&)) override;
    int getSize() const override;

private:
    Array(size_t arraySize);
};
}

#include "collections/array.inl"
