#pragma once

#include "memory/managedobject.h"
#include "memory/memorymanager.h"

template <class T>
class Array : public ManagedObject {
    int arraySize;

public:
    typedef T *iterator;

    static Array *create(int size);

    ~Array();

    iterator begin();
    iterator end();

    T *data() const;

    T *operator*() const;
    T &operator[](int index) const;

    int size() const;

    void mapOnReferences(void (*f)(ManagedObject *&)) override;
    int getSize() const override;

private:
    Array(int arraySize);
};

template <class T>
Array<T> *Array<T>::create(int size) {
    Array<T> *array = static_cast<Array<T> *>(MemoryManager::allocate(sizeof(Array) + size * sizeof(T)));
    new (array) Array<T>(size);
    new (**array) T[size];
    return array;
}

template <class T>
Array<T>::~Array() {
    delete[] data();
}

template <class T>
typename Array<T>::iterator Array<T>::begin() {
    return data();
}

template <class T>
typename Array<T>::iterator Array<T>::end() {
    return data() + arraySize;
}

template <class T>
T *Array<T>::data() const {
    return reinterpret_cast<T *>(const_cast<Array<T> *>(this) + 1);
}

template <class T>
T *Array<T>::operator*() const {
    return data();
}

template <class T>
T &Array<T>::operator[](int index) const {
    return data()[index];
}

template <class T>
int Array<T>::size() const {
    return arraySize;
}

template <class T>
void Array<T>::mapOnReferences(void (*)(ManagedObject *&)) {
}

template <class T>
int Array<T>::getSize() const {
    return sizeof(*this) + arraySize * sizeof(T);
}

template <class T>
Array<T>::Array(int size)
    : arraySize(size) {
}
