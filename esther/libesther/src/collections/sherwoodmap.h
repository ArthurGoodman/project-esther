#pragma once

#include "collections/map.h"

template <class>
class Array;

template <class K, class V>
class SherwoodMap : public Map<K, V> {
    class Entry {
        uint hash;
        K key;
        V value;

    public:
        static uint deletedFlag();

        Entry();
        Entry(uint hash, K key, V value);

        K &getKey();
        V &getValue();
        uint &getHash();

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
    int getSize() const override;

private:
    static uint computeHash(const K &key);
    static uint hashKey(const K &key);

    void allocate();
    int probeDistance(uint hash, uint index) const;
    V &insert(uint hash, K key, V value);
    int lookup(const K &key) const;
};

template <class K, class V>
inline uint SherwoodMap<K, V>::Entry::deletedFlag() {
    return 1 << (sizeof(hash) * 8 - 1);
}

template <class K, class V>
inline bool SherwoodMap<K, V>::Entry::isDeleted() {
    return hash & deletedFlag();
}

template <class K, class V>
inline int SherwoodMap<K, V>::probeDistance(uint hash, uint index) const {
    return (index + capacity - (hash & mask)) & mask;
}
