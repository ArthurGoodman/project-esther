#pragma once

#include "collections/map.h"

namespace es {

template <class>
class Array;

template <class K, class V>
class SherwoodMap : public Map<K, V> {
    class Entry {
        uint32_t hash;
        K key;
        V value;

    public:
        static uint32_t deletedFlag();

        Entry();
        Entry(uint32_t hash, K key, V value);

        K &getKey();
        V &getValue();
        uint32_t &getHash();

        void clear();
        bool isDeleted();

        bool equals(const K &key);
    };

    friend class Array<Entry>;

    static const int HalfInitialCapacity = 4;
    static const int LoadFactorPercent = 90;

    Array<Entry> *buffer;
    int numEntries, capacity, resizeThreshold, mask;

public:
    class iterator {
        friend class SherwoodMap;

        Array<Entry> *buffer;
        int capacity, index;

    public:
        iterator &operator++();
        iterator &operator*();

        bool operator!=(const iterator &other) const;

        K &key();
        V &value();

    private:
        iterator(Array<Entry> *buffer, int capacity, int index);
    };

    SherwoodMap();

    iterator begin();
    iterator end();

    V &get(const K &key) const override;
    V &put(const K &key, const V &value) override;
    bool remove(const K &key) override;
    bool contains(const K &key) const override;

    int size() const override;

    void mapOnReferences(void (*f)(ManagedObject *&)) override;

private:
    static uint32_t computeHash(const K &key);
    static uint32_t hashKey(const K &key);

    void allocate();
    int probeDistance(uint32_t hash, uint32_t index) const;
    V &insert(uint32_t hash, K key, V value);
    int lookup(const K &key) const;
};

template <class K, class V>
inline uint32_t SherwoodMap<K, V>::Entry::deletedFlag() {
    return 1 << (sizeof(hash) * 8 - 1);
}

template <class K, class V>
inline bool SherwoodMap<K, V>::Entry::isDeleted() {
    return hash & deletedFlag();
}

template <class K, class V>
inline int SherwoodMap<K, V>::probeDistance(uint32_t hash, uint32_t index) const {
    return (index + capacity - (hash & mask)) & mask;
}
}

#include "collections/sherwoodmap.inl"
