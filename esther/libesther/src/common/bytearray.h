#pragma once

#include <cstdint>

class ByteArray {
    uint32_t size, capacity;
    uint8_t *data;

public:
    ByteArray(uint32_t initialCapacity = 0);

    ByteArray(const ByteArray &array);
    ByteArray(ByteArray &&array);

    ~ByteArray();

    ByteArray &operator=(const ByteArray &array);
    ByteArray &operator=(ByteArray &&array);

    uint8_t *allocate(uint32_t count);
    int reallocate();

    template <class T>
    ByteArray &push(T value);

    template <class T>
    T pop();

    uint8_t &operator[](int index);

    bool free(uint32_t count);
    void release();

    bool enoughSpace(uint32_t count) const;

    uint8_t *getData() const;
    uint32_t getSize() const;
    uint32_t getCapacity() const;
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
