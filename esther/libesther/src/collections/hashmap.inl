#include "collections/hashmap.h"

#include <stdexcept>

#include "runtime/object.h"
#include "collections/array.h"

namespace es {

template <class K, class V>
HashMap<K, V>::Entry::Entry(const K &key, const V &value)
    : key(key)
    , value(value)
    , next(0) {
}

template <class K, class V>
K &HashMap<K, V>::Entry::getKey() {
    return key;
}

template <class K, class V>
V &HashMap<K, V>::Entry::getValue() {
    return value;
}

template <class K, class V>
void HashMap<K, V>::Entry::setKey(const K &key) {
    this->key = key;
}

template <class K, class V>
void HashMap<K, V>::Entry::setValue(const V &value) {
    this->value = value;
}

template <class K, class V>
typename HashMap<K, V>::Entry *HashMap<K, V>::Entry::getNext() const {
    return next;
}

template <class K, class V>
void HashMap<K, V>::Entry::setNext(Entry *next) {
    this->next = next;
}

template <class K, class V>
bool HashMap<K, V>::Entry::equals(const K &key) const {
    return this->key == key;
}

template <>
inline bool HashMap<Object *, uint32_t>::Entry::equals(Object *const & /*key*/) const {
    // return this->key->equals(key);
    return false;
}

template <class K, class V>
void HashMap<K, V>::Entry::mapOnReferences(void (*f)(ManagedObject *&)) {
    if (next)
        f(reinterpret_cast<ManagedObject *&>(next));
}

template <>
inline void HashMap<uint32_t, Object *>::Entry::mapOnReferences(void (*f)(ManagedObject *&)) {
    if (next)
        f(reinterpret_cast<ManagedObject *&>(next));

    if (value)
        f(reinterpret_cast<ManagedObject *&>(value));
}

template <>
inline void HashMap<Object *, uint32_t>::Entry::mapOnReferences(void (*f)(ManagedObject *&)) {
    if (next)
        f(reinterpret_cast<ManagedObject *&>(next));

    if (key)
        f(reinterpret_cast<ManagedObject *&>(key));
}

template <class K, class V>
typename HashMap<K, V>::iterator &HashMap<K, V>::iterator::operator++() {
    if (entry->getNext())
        entry = entry->getNext();
    else {
        while (++i < capacity)
            if ((*buffer)[i]) {
                entry = (*buffer)[i];
                break;
            }

        if (i == capacity)
            entry = 0;
    }

    return *this;
}

template <class K, class V>
typename HashMap<K, V>::iterator &HashMap<K, V>::iterator::operator*() {
    return *this;
}

template <class K, class V>
bool HashMap<K, V>::iterator::operator!=(const iterator &other) const {
    return entry != ((const HashMap::iterator &)other).entry;
}

template <class K, class V>
K &HashMap<K, V>::iterator::key() {
    return entry->getKey();
}

template <class K, class V>
V &HashMap<K, V>::iterator::value() {
    return entry->getValue();
}

template <class K, class V>
HashMap<K, V>::iterator::iterator()
    : buffer(0)
    , entry(0)
    , capacity(0)
    , i(0) {
}

template <class K, class V>
HashMap<K, V>::iterator::iterator(Array<Entry *> *buffer, int capacity, int i)
    : buffer(buffer)
    , entry((*buffer)[i])
    , capacity(capacity)
    , i(i) {
}

template <class K, class V>
HashMap<K, V>::HashMap()
    : buffer(0)
    , numEntries(0)
    , capacity(HalfInitialCapacity)
    , resizeThreshold(0) {
}

template <class K, class V>
typename HashMap<K, V>::iterator HashMap<K, V>::begin() {
    for (int i = 0; i < capacity; i++)
        if ((*buffer)[i])
            return iterator(buffer, capacity, i);

    return iterator();
}

template <class K, class V>
typename HashMap<K, V>::iterator HashMap<K, V>::end() {
    return iterator();
}

template <class K, class V>
V &HashMap<K, V>::get(const K &key) const {
    Entry *entry = lookup(key);

    if (entry == 0)
        throw std::out_of_range("HashMap<K, V>::get");

    return entry->getValue();
}

template <class K, class V>
V &HashMap<K, V>::put(const K &key, const V &value) {
    Ptr<HashMap> _this = this;

    if (++numEntries >= resizeThreshold)
        allocate();

    return _this->insert(key, value);
}

template <>
inline Object *&HashMap<uint32_t, Object *>::put(const uint32_t &key, Object *const &value) {
    Ptr<HashMap> _this = this;
    Ptr<Object> pValue = value;

    if (++numEntries >= resizeThreshold)
        allocate();

    return _this->insert(key, pValue);
}

template <>
inline uint32_t &HashMap<Object *, uint32_t>::put(Object *const &key, const uint32_t &value) {
    Ptr<HashMap> _this = this;
    Ptr<Object> pKey = key;

    if (++numEntries >= resizeThreshold)
        allocate();

    return _this->insert(pKey, value);
}

template <class K, class V>
bool HashMap<K, V>::remove(const K &key) {
    if (buffer == 0)
        return false;

    int hashValue = hashKey(key) & mask;

    Entry *prev = 0;
    Entry *entry = (*buffer)[hashValue];

    while (entry && !entry->equals(key)) {
        prev = entry;
        entry = entry->getNext();
    }

    if (entry == 0)
        return false;

    if (prev == 0)
        (*buffer)[hashValue] = entry->getNext();
    else
        prev->setNext(entry->getNext());

    numEntries--;

    return true;
}

template <class K, class V>
bool HashMap<K, V>::contains(const K &key) const {
    return lookup(key) != 0;
}

template <class K, class V>
int HashMap<K, V>::size() const {
    return numEntries;
}

template <>
inline void Array<typename HashMap<uint32_t, Object *>::Entry *>::mapOnReferences(void (*f)(ManagedObject *&)) {
    for (int i = 0; i < size(); i++)
        if (data()[i])
            f(reinterpret_cast<ManagedObject *&>(data()[i]));
}

template <>
inline void Array<typename HashMap<Object *, uint32_t>::Entry *>::mapOnReferences(void (*f)(ManagedObject *&)) {
    for (int i = 0; i < size(); i++)
        if (data()[i])
            f(reinterpret_cast<ManagedObject *&>(data()[i]));
}

template <class K, class V>
void HashMap<K, V>::mapOnReferences(void (*f)(ManagedObject *&)) {
    if (buffer)
        f(reinterpret_cast<ManagedObject *&>(buffer));
}

template <class K, class V>
uint64_t HashMap<K, V>::hashKey(const K &key) {
    return std::hash<K>()(key);
}

template <>
inline uint64_t HashMap<Object *, uint32_t>::hashKey(Object *const & /*key*/) {
    // return key->hash();
    return 0;
}

template <class K, class V>
void HashMap<K, V>::allocate() {
    Ptr<HashMap> _this = this;
    Ptr<Array<Entry *>> oldEntries = buffer;

    int oldCapacity = buffer ? capacity : 0;

    Array<Entry *> *newBuffer = Array<Entry *>::create(capacity * 2);
    _this->buffer = newBuffer;
    _this->capacity *= 2;
    _this->resizeThreshold = (_this->capacity * LoadFactorPercent) / 100;
    _this->mask = _this->capacity - 1;

    for (Entry *&entry : *_this->buffer)
        entry = 0;

    for (int i = 0; i < oldCapacity; i++) {
        Entry *prev = 0;
        Entry *entry = (**oldEntries)[i];

        while (entry) {
            uint32_t hashValue = hashKey(entry->getKey()) & _this->mask;

            prev = entry;
            entry = entry->getNext();

            prev->setNext((*_this->buffer)[hashValue]);
            (*_this->buffer)[hashValue] = prev;
        }
    }
}

template <class K, class V>
V &HashMap<K, V>::insert(const K &key, const V &value) {
    int hashValue = hashKey(key) & mask;

    Ptr<Entry> prev = 0;
    Ptr<Entry> entry = (*buffer)[hashValue];
    Ptr<HashMap> _this = this;

    while (entry && !entry->equals(key)) {
        prev = entry;
        entry = entry->getNext();
    }

    if (entry) {
        entry->setValue(value);
        numEntries--;
        return entry->getValue();
    }

    entry = createEntry(key, value);

    if (prev == 0)
        (*_this->buffer)[hashValue] = entry;
    else
        prev->setNext(entry);

    return entry->getValue();
}

template <class K, class V>
typename HashMap<K, V>::Entry *HashMap<K, V>::lookup(const K &key) const {
    if (buffer == 0)
        return 0;

    Entry *entry = (*buffer)[hashKey(key) & mask];

    while (entry && !entry->equals(key))
        entry = entry->getNext();

    return entry;
}

template <class K, class V>
typename HashMap<K, V>::Entry *HashMap<K, V>::createEntry(const K &key, const V &value) const {
    return new Entry(key, value);
}

template <>
inline typename HashMap<uint32_t, Object *>::Entry *HashMap<uint32_t, Object *>::createEntry(const uint32_t &key, Object *const &value) const {
    Ptr<Object> pValue = value;

    Entry *entry = new Entry(key, 0);
    entry->setValue(pValue);

    return entry;
}

template <>
inline typename HashMap<Object *, uint32_t>::Entry *HashMap<Object *, uint32_t>::createEntry(Object *const &key, const uint32_t &value) const {
    Ptr<Object> pKey = key;

    Entry *entry = new Entry(0, value);
    entry->setKey(pKey);

    return entry;
}
}
