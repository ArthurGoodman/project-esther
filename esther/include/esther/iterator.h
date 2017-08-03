#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"
#include "esther/std_map.h"

Object *RangeIterator_new(Esther *es, int64_t start, int64_t stop, int64_t step);
Object *RangeIterator_next(Esther *es, Object *self);

Object *Range_iterator(Esther *es, Object *self);
Object *Range_reversed(Esther *es, Object *self);

typedef struct SequenceIterator {
    Object base;

    Object *sequence;
    size_t index;
    bool reversed;
} SequenceIterator;

#define as_SequenceIterator(obj) ((SequenceIterator *) (obj))

Object *SequenceIterator_new(Esther *es, Object *sequence, bool reversed);
Object *SequenceIterator_next(Esther *es, Object *self);

Object *Iterable_iterator(Esther *es, Object *self);
Object *Iterable_reversed(Esther *es, Object *self);

typedef struct MapIterator {
    Object base;

    Object *map;
    std_map_iterator i;
} MapIterator;

#define as_MapIterator(obj) ((MapIterator *) (obj))

Object *MapIterator_new(Esther *es, Object *map);
Object *MapIterator_next(Esther *es, Object *self);

Object *Map_iterator(Esther *es, Object *self);
Object *Map_reversed(Esther *es, Object *self);

#ifdef __cplusplus
}
#endif
