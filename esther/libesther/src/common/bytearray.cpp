#include "bytearray.h"

#include <memory>

#include "common/utility.h"

ByteArray::ByteArray(uint32_t initialCapacity)
    : size(0)
    , capacity(0)
    , data(0) {
    allocate(initialCapacity);
    free(initialCapacity);
}

ByteArray::ByteArray(const ByteArray &array)
    : data(0) {
    *this = array;
}

ByteArray::ByteArray(ByteArray &&array)
    : data(0) {
    *this = std::move(array);
}

ByteArray::~ByteArray() {
    release();
}

ByteArray &ByteArray::operator=(const ByteArray &array) {
    size = array.size;
    capacity = array.capacity;

    ::free(data);

    data = (uint8_t *)malloc(capacity);
    memcpy(data, array.data, size);

    return *this;
}

ByteArray &ByteArray::operator=(ByteArray &&array) {
    size = array.size;
    capacity = array.capacity;

    ::free(data);

    data = array.data;

    array.data = 0;
    array.size = 0;
    array.capacity = 0;

    return *this;
}

uint8_t *ByteArray::allocate(uint32_t count) {
    if (!enoughSpace(count)) {
        uint32_t newCapacity = Utility::ceilToPowerOf2(size + count);

        uint8_t *newData = (uint8_t *)realloc(data, newCapacity);

        if (!newData)
            return 0;

        capacity = newCapacity;
        data = newData;
    }

    size += count;

    return data + size - count;
}

int ByteArray::reallocate() {
    uint8_t *newData = (uint8_t *)malloc(capacity);

    if (!newData)
        return 0;

    memcpy(newData, data, size);

    int delta = newData - data;

    ::free(data);
    data = newData;

    return delta;
}

uint8_t &ByteArray::operator[](int index) {
    return data[index];
}

bool ByteArray::free(uint32_t count) {
    if (size < count)
        return false;

    size -= count;
    return true;
}

void ByteArray::release() {
    ::free(data);

    size = 0;
    capacity = 0;
    data = 0;
}

bool ByteArray::enoughSpace(uint32_t count) const {
    return size + count <= capacity;
}

uint8_t *ByteArray::getData() const {
    return data;
}

uint32_t ByteArray::getSize() const {
    return size;
}

uint32_t ByteArray::getCapacity() const {
    return capacity;
}
