#include "collections/sherwoodmap.h"

#include "runtime/object.h"
#include "collections/array.h"

namespace es {

template <class K, class V>
SherwoodMap<K, V>::Entry::Entry()
    : hash(0) {
}

template <>
inline SherwoodMap<uint32_t, Object *>::Entry::Entry()
    : hash(0)
    , value(0) {
}

template <>
inline SherwoodMap<Object *, uint32_t>::Entry::Entry()
    : hash(0)
    , key(0) {
}

template <class K, class V>
SherwoodMap<K, V>::Entry::Entry(uint32_t hash, K key, V value)
    : hash(hash)
    , key(key)
    , value(value) {
}

template <class K, class V>
K &SherwoodMap<K, V>::Entry::getKey() {
    return key;
}

template <class K, class V>
V &SherwoodMap<K, V>::Entry::getValue() {
    return value;
}

template <class K, class V>
uint32_t &SherwoodMap<K, V>::Entry::getHash() {
    return hash;
}

template <class K, class V>
void SherwoodMap<K, V>::Entry::clear() {
    hash |= deletedFlag();
}

template <>
inline void SherwoodMap<uint32_t, Object *>::Entry::clear() {
    hash |= deletedFlag();
    value = 0;
}

template <>
inline void SherwoodMap<Object *, uint32_t>::Entry::clear() {
    hash |= deletedFlag();
    key = 0;
}

template <class K, class V>
bool SherwoodMap<K, V>::Entry::equals(const K &key) {
    return this->key == key;
}

template <>
inline bool SherwoodMap<Object *, uint32_t>::Entry::equals(Object *const & /*key*/) {
    // return this->key->equals(key);
    return false;
}

template <class K, class V>
typename SherwoodMap<K, V>::iterator &SherwoodMap<K, V>::iterator::operator++() {
    while (++index < capacity && ((*buffer)[index].getHash() == 0 || (*buffer)[index].isDeleted())) {
    }

    return *this;
}

template <class K, class V>
typename SherwoodMap<K, V>::iterator &SherwoodMap<K, V>::iterator::operator*() {
    return *this;
}

template <class K, class V>
bool SherwoodMap<K, V>::iterator::operator!=(const iterator &other) const {
    return index != other.index;
}

template <class K, class V>
K &SherwoodMap<K, V>::iterator::key() {
    return (*buffer)[index].getKey();
}

template <class K, class V>
V &SherwoodMap<K, V>::iterator::value() {
    return (*buffer)[index].getValue();
}

template <class K, class V>
SherwoodMap<K, V>::iterator::iterator(Array<Entry> *buffer, int capacity, int index)
    : buffer(buffer)
    , capacity(capacity)
    , index(index) {
}

template <class K, class V>
SherwoodMap<K, V>::SherwoodMap()
    : buffer(0)
    , numEntries(0)
    , capacity(HalfInitialCapacity)
    , resizeThreshold(0) {
}

template <class K, class V>
typename SherwoodMap<K, V>::iterator SherwoodMap<K, V>::begin() {
    if (numEntries == 0)
        return iterator(buffer, capacity, capacity);

    for (int i = 0; i < capacity; i++)
        if ((*buffer)[i].getHash() && !(*buffer)[i].isDeleted())
            return iterator(buffer, capacity, i);

    return iterator(buffer, capacity, capacity);
}

template <class K, class V>
typename SherwoodMap<K, V>::iterator SherwoodMap<K, V>::end() {
    return iterator(buffer, capacity, capacity);
}

template <class K, class V>
V &SherwoodMap<K, V>::get(const K &key) const {
    const int index = lookup(key);

    if (index == -1)
        throw std::out_of_range("SherwoodMap<K, V>::get");

    return (*buffer)[index].getValue();
}

template <class K, class V>
V &SherwoodMap<K, V>::put(const K &key, const V &value) {
    Ptr<SherwoodMap> _this = this;

    if (++numEntries >= resizeThreshold)
        allocate();

    return _this->insert(hashKey(key), key, value);
}

template <>
inline Object *&SherwoodMap<uint32_t, Object *>::put(const uint32_t &key, Object *const &value) {
    Ptr<SherwoodMap> _this = this;
    Ptr<Object> pValue = value;

    if (++numEntries >= resizeThreshold)
        allocate();

    return _this->insert(hashKey(key), key, pValue);
}

template <>
inline uint32_t &SherwoodMap<Object *, uint32_t>::put(Object *const &key, const uint32_t &value) {
    Ptr<SherwoodMap> _this = this;
    Ptr<Object> pKey = key;

    if (++numEntries >= resizeThreshold)
        allocate();

    return _this->insert(hashKey(pKey), pKey, value);
}

template <class K, class V>
bool SherwoodMap<K, V>::remove(const K &key) {
    const int index = lookup(key);

    if (index == -1)
        return false;

    (*buffer)[index].clear();
    numEntries--;

    return true;
}

template <class K, class V>
bool SherwoodMap<K, V>::contains(const K &key) const {
    return lookup(key) != -1;
}

template <class K, class V>
int SherwoodMap<K, V>::size() const {
    return numEntries;
}

template <>
inline void Array<typename SherwoodMap<uint32_t, Object *>::Entry>::mapOnReferences(void (*f)(ManagedObject *&)) {
    for (int i = 0; i < size(); i++)
        if (data()[i].getValue())
            f(reinterpret_cast<ManagedObject *&>(data()[i].getValue()));
}

template <>
inline void Array<typename SherwoodMap<Object *, uint32_t>::Entry>::mapOnReferences(void (*f)(ManagedObject *&)) {
    for (int i = 0; i < size(); i++)
        if (data()[i].getKey())
            f(reinterpret_cast<ManagedObject *&>(data()[i].getKey()));
}

template <class K, class V>
void SherwoodMap<K, V>::mapOnReferences(void (*f)(ManagedObject *&)) {
    if (buffer)
        f(reinterpret_cast<ManagedObject *&>(buffer));
}

template <class K, class V>
int SherwoodMap<K, V>::getSize() const {
    return sizeof *this;
}

template <class K, class V>
uint32_t SherwoodMap<K, V>::computeHash(const K &key) {
    return std::hash<K>()(key);
}

template <>
inline uint32_t SherwoodMap<Object *, uint32_t>::computeHash(Object *const & /*key*/) {
    // return key->hash();
    return 0;
}

template <class K, class V>
uint32_t SherwoodMap<K, V>::hashKey(const K &key) {
    uint32_t hash = computeHash(key);

    hash &= ~Entry::deletedFlag();
    hash |= hash == 0;

    return hash;
}

template <class K, class V>
void SherwoodMap<K, V>::allocate() {
    Ptr<SherwoodMap> _this = this;
    Ptr<Array<Entry>> oldEntries = buffer;

    int oldCapacity = buffer ? capacity : 0;

    Array<Entry> *newBuffer = Array<Entry>::create(capacity * 2);
    _this->buffer = newBuffer;
    _this->capacity *= 2;
    _this->resizeThreshold = (_this->capacity * LoadFactorPercent) / 100;
    _this->mask = _this->capacity - 1;

    for (int i = 0; i < oldCapacity; i++) {
        Entry &entry = (**oldEntries)[i];

        if (entry.getHash() && !entry.isDeleted())
            _this->insert(entry.getHash(), entry.getKey(), entry.getValue());
    }
}

template <class K, class V>
V &SherwoodMap<K, V>::insert(uint32_t hash, K key, V value) {
    int index = hash & mask;
    int dist = 0;

    while (true) {
        if ((*buffer)[index].getHash() == 0) {
            new (**buffer + index) Entry(hash, key, value);
            return (*buffer)[index].getValue();
        }

        if ((*buffer)[index].getHash() == hash && (*buffer)[index].equals(key)) {
            new (**buffer + index) Entry(hash, key, value);
            numEntries--;
            return (*buffer)[index].getValue();
        }

        int existingEntryProbeDist = probeDistance((*buffer)[index].getHash(), index);
        int returnIndex = -1;

        if (dist > existingEntryProbeDist) {
            if ((*buffer)[index].isDeleted()) {
                new (**buffer + index) Entry(hash, key, value);
                return (*buffer)[returnIndex].getValue();
            }

            if (returnIndex == -1)
                returnIndex = index;

            std::swap(hash, (*buffer)[index].getHash());
            std::swap(key, (*buffer)[index].getKey());
            std::swap(value, (*buffer)[index].getValue());

            dist = existingEntryProbeDist;
        }

        index = (index + 1) & mask;
        dist++;
    }
}

template <class K, class V>
int SherwoodMap<K, V>::lookup(const K &key) const {
    const uint32_t hash = hashKey(key);

    int index = hash & mask;
    int dist = 0;

    while (true) {
        if (buffer == 0 || (*buffer)[index].getHash() == 0)
            return -1;
        else if (dist > probeDistance((*buffer)[index].getHash(), index))
            return -1;
        else if ((*buffer)[index].getHash() == hash && (*buffer)[index].equals(key))
            return index;

        index = (index + 1) & mask;
        dist++;
    }
}
}
