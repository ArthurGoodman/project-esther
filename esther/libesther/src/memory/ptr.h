#pragma once

namespace es {

template <class T>
class Ptr {
public:
    T *ptr;
    Ptr *prev = nullptr, *next = nullptr;

public:
    Ptr(T *p = nullptr);
    Ptr(const Ptr<T> &p);
    ~Ptr();

    Ptr<T> &operator=(T *p);
    Ptr<T> &operator=(const Ptr<T> &p);

    T *&operator*();
    T *operator*() const;
    T *operator->() const;
    operator T *() const;

private:
    void link();
    void unlink();
};

extern Ptr<void> *pointers;
}

#include "memory/ptr.inl"
