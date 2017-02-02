#pragma once

template <class T>
class Ptr {
public:
    T *pointer;
    Ptr *prev, *next;

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

template <class T>
Ptr<T>::Ptr(T *p)
    : pointer(p)
    , prev(nullptr)
    , next(nullptr) {
    link();
}

template <class T>
Ptr<T>::Ptr(const Ptr<T> &p)
    : pointer(p)
    , prev(nullptr)
    , next(nullptr) {
    link();
}

template <class T>
Ptr<T>::~Ptr() {
    unlink();
}

template <class T>
Ptr<T> &Ptr<T>::operator=(T *p) {
    pointer = p;
    return *this;
}

template <class T>
Ptr<T> &Ptr<T>::operator=(const Ptr<T> &p) {
    pointer = p.pointer;
    return *this;
}

template <class T>
T *&Ptr<T>::operator*() {
    return pointer;
}

template <class T>
T *Ptr<T>::operator*() const {
    return pointer;
}

template <class T>
T *Ptr<T>::operator->() const {
    return pointer;
}

template <class T>
Ptr<T>::operator T *() const {
    return pointer;
}

template <class T>
void Ptr<T>::link() {
    next = reinterpret_cast<Ptr *>(pointers);

    if (next)
        next->prev = this;

    pointers = reinterpret_cast<Ptr<void> *>(this);
}

template <class T>
void Ptr<T>::unlink() {
    if (prev)
        prev->next = next;
    else
        pointers = reinterpret_cast<Ptr<void> *>(next);

    if (next)
        next->prev = prev;
}
