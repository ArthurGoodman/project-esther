#include "memory/ptr.h"

#include "common/config.h"

namespace es {

template <class T>
Ptr<T>::Ptr(T *p)
    : ptr(p) {
#ifdef GC
    link();
#endif
}

template <class T>
Ptr<T>::Ptr(const Ptr<T> &p)
    : ptr(p) {
#ifdef GC
    link();
#endif
}

template <class T>
Ptr<T>::~Ptr() {
#ifdef GC
    unlink();
#endif
}

template <class T>
Ptr<T> &Ptr<T>::operator=(T *p) {
    ptr = p;
    return *this;
}

template <class T>
Ptr<T> &Ptr<T>::operator=(const Ptr<T> &p) {
    ptr = p.ptr;
    return *this;
}

template <class T>
T *&Ptr<T>::operator*() {
    return ptr;
}

template <class T>
T *Ptr<T>::operator*() const {
    return ptr;
}

template <class T>
T *Ptr<T>::operator->() const {
    return ptr;
}

template <class T>
Ptr<T>::operator T *() const {
    return ptr;
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
}
