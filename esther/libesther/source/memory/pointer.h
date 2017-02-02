#pragma once

class ManagedObject;

template <class T>
class Ptr {
public:
    struct Aux {
        T *pointer;
        Aux *prev, *next;
    };

private:
    Aux *aux;

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

    void link(Aux *&pointers);
    void unlink(Aux *&pointers);
};

extern Ptr<ManagedObject>::Aux *pointers;

template <class T>
Ptr<T>::Ptr(T *p)
    : aux(new Aux({ p, nullptr, nullptr })) {
    link((Ptr<T>::Aux *&)pointers);
}

template <class T>
Ptr<T>::Ptr(const Ptr<T> &p)
    : aux(new Aux({ p.aux->pointer, nullptr, nullptr })) {
    link((Ptr<T>::Aux *&)pointers);
}

template <class T>
Ptr<T>::~Ptr() {
    unlink((Ptr<T>::Aux *&)pointers);
    delete aux;
}

template <class T>
Ptr<T> &Ptr<T>::operator=(const Ptr<T> &p) {
    aux->pointer = p.aux->pointer;
    return *this;
}

template <class T>
T *&Ptr<T>::operator*() {
    return aux->pointer;
}

template <class T>
T *Ptr<T>::operator*() const {
    return aux->pointer;
}

template <class T>
T *Ptr<T>::operator->() const {
    return aux->pointer;
}

template <class T>
Ptr<T>::operator T *() const {
    return aux->pointer;
}

template <class T>
Ptr<T> &Ptr<T>::operator=(T *p) {
    aux->pointer = p;
    return *this;
}

template <class T>
void Ptr<T>::link(Ptr<T>::Aux *&pointers) {
    aux->next = pointers;

    if (pointers)
        pointers->prev = aux;

    pointers = aux;
}

template <class T>
void Ptr<T>::unlink(Ptr<T>::Aux *&pointers) {
    if (aux->next)
        aux->next->prev = aux->prev;

    if (aux->prev)
        aux->prev->next = aux->next;

    if (pointers == aux)
        pointers = pointers->next;
}
