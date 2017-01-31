#pragma once

class ManagedObject;

template <class T>
class Pointer {
public:
    struct Aux {
        T *pointer;
        Aux *prev, *next;
    };

private:
    Aux *aux;

public:
    Pointer(T *p = nullptr);
    Pointer(const Pointer<T> &p);
    ~Pointer();

    Pointer<T> &operator=(T *p);
    Pointer<T> &operator=(const Pointer<T> &p);

    T *&operator*();
    T *operator*() const;
    T *operator->() const;
    operator T *() const;

    void link(Aux *&pointers);
    void unlink(Aux *&pointers);
};

extern Pointer<ManagedObject>::Aux *pointers;

template <class T>
Pointer<T>::Pointer(T *p)
    : aux(new Aux({ p, nullptr, nullptr })) {
    link((Pointer<T>::Aux *&)pointers);
}

template <class T>
Pointer<T>::Pointer(const Pointer<T> &p)
    : Pointer(p.aux->pointer) {
}

template <class T>
Pointer<T>::~Pointer() {
    unlink((Pointer<T>::Aux *&)pointers);
    delete aux;
}

template <class T>
Pointer<T> &Pointer<T>::operator=(const Pointer<T> &p) {
    aux->pointer = p.aux->pointer;
    return *this;
}

template <class T>
T *&Pointer<T>::operator*() {
    return aux->pointer;
}

template <class T>
T *Pointer<T>::operator*() const {
    return aux->pointer;
}

template <class T>
T *Pointer<T>::operator->() const {
    return aux->pointer;
}

template <class T>
Pointer<T>::operator T *() const {
    return aux->pointer;
}

template <class T>
Pointer<T> &Pointer<T>::operator=(T *p) {
    aux->pointer = p;
    return *this;
}

template <class T>
void Pointer<T>::link(Pointer<T>::Aux *&pointers) {
    aux->next = pointers;

    if (pointers)
        pointers->prev = aux;

    pointers = aux;
}

template <class T>
void Pointer<T>::unlink(Pointer<T>::Aux *&pointers) {
    if (aux->next)
        aux->next->prev = aux->prev;

    if (aux->prev)
        aux->prev->next = aux->next;

    if (pointers == aux)
        pointers = pointers->next;
}
