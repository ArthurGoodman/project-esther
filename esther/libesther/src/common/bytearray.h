#pragma once

#include <cstddef>
#include <cstdint>

namespace es {

class ByteArray {
    size_t size, capacity;
    uint8_t *data;

public:
    ByteArray(size_t initialCapacity = 0);

    ByteArray(const ByteArray &array);
    ByteArray(ByteArray &&array);

    ~ByteArray();

    ByteArray &operator=(const ByteArray &array);
    ByteArray &operator=(ByteArray &&array);

    uint8_t *allocate(size_t count);
    int reallocate();

    template <class T>
    ByteArray &push(T value);

    template <class T>
    T pop();

    uint8_t &operator[](int index);

    bool free(size_t count);
    void release();

    bool enoughSpace(size_t count) const;

    uint8_t *getData() const;
    size_t getSize() const;
    size_t getCapacity() const;
};

template <class T>
ByteArray &ByteArray::push(T value) {
    *reinterpret_cast<T *>(allocate(sizeof(T))) = value;
    return *this;
}

template <class T>
T ByteArray::pop() {
    free(sizeof(T));
    return *reinterpret_cast<T *>(data + size);
}
}
