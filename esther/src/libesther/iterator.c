#include "esther/iterator.h"

#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/map.h"
#include "esther/range.h"
#include "esther/valueobject.h"

Object *RangeIterator_new(Esther *es, int64_t start, int64_t stop, int64_t step) {
    Object *self = gc_alloc(sizeof(Range));

    Object_init(es, self, TObject, Esther_getRootObject(es, cstr_to_id("RangeIterator")));

    as_Range(self)->start = start;
    as_Range(self)->stop = stop;
    as_Range(self)->step = step;

    *(void **) self = &vtable_for_Object;

    return self;
}

Object *RangeIterator_next(Esther *es, Object *self) {
    if (as_Range(self)->start == as_Range(self)->stop)
        Exception_throw(Exception_new_stopIteration(es));

    as_Range(self)->start += as_Range(self)->step;

    return ValueObject_new_int(es, as_Range(self)->start - as_Range(self)->step);
}

Object *Range_iterator(Esther *es, Object *self) {
    return RangeIterator_new(es, as_Range(self)->start, as_Range(self)->stop, as_Range(self)->step);
}

Object *Range_reversed(Esther *es, Object *self) {
    return RangeIterator_new(es, as_Range(self)->stop, as_Range(self)->start, -as_Range(self)->step);
}

#define SequenceIterator_virtual_finalize Object_virtual_finalize
#define SequenceIterator_virtual_clone Object_virtual_clone_unimplemented

void SequenceIterator_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    Object_virtual_mapOnRefs(self, f);

    f(as_SequenceIterator(self)->sequence);
}

OBJECT_VTABLE(SequenceIterator)

Object *SequenceIterator_new(Esther *es, Object *sequence, bool reversed) {
    Object *self = gc_alloc(sizeof(SequenceIterator));

    Object_init(es, self, TObject, Esther_getRootObject(es, cstr_to_id("SequenceIterator")));

    size_t size = Variant_toInt(ValueObject_getValue(Object_call(es, sequence, cstr_to_id("size"), 0)));

    as_SequenceIterator(self)->sequence = sequence;
    as_SequenceIterator(self)->index = reversed ? size - 1 : 0;
    as_SequenceIterator(self)->reversed = reversed;

    *(void **) self = &vtable_for_SequenceIterator;

    return self;
}

Object *SequenceIterator_next(Esther *es, Object *self) {
    size_t size = Variant_toInt(ValueObject_getValue(Object_call(es, as_SequenceIterator(self)->sequence, cstr_to_id("size"), 0)));

    if ((as_SequenceIterator(self)->reversed && as_SequenceIterator(self)->index == (size_t) -1) || as_SequenceIterator(self)->index == size)
        Exception_throw(Exception_new_stopIteration(es));

    Object *value = Object_call(es, as_SequenceIterator(self)->sequence, cstr_to_id("at"), 1, ValueObject_new_int(es, as_SequenceIterator(self)->index));

    if (as_SequenceIterator(self)->reversed)
        as_SequenceIterator(self)->index--;
    else
        as_SequenceIterator(self)->index++;

    return value;
}

Object *Iterable_iterator(Esther *es, Object *self) {
    return SequenceIterator_new(es, self, false);
}

Object *Iterable_reversed(Esther *es, Object *self) {
    return SequenceIterator_new(es, self, true);
}

#define MapIterator_virtual_finalize Object_virtual_finalize
#define MapIterator_virtual_clone Object_virtual_clone_unimplemented

void MapIterator_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    Object_virtual_mapOnRefs(self, f);

    f(as_MapIterator(self)->map);
}

OBJECT_VTABLE(MapIterator)

Object *MapIterator_new(Esther *es, Object *map) {
    Object *self = gc_alloc(sizeof(MapIterator));

    Object_init(es, self, TObject, Esther_getRootObject(es, cstr_to_id("MapIterator")));

    as_MapIterator(self)->map = map;
    std_map_begin(as_Map(map)->data, &as_MapIterator(self)->i);

    *(void **) self = &vtable_for_MapIterator;

    return self;
}

Object *MapIterator_next(Esther *es, Object *self) {
    if (std_map_end(as_Map(as_MapIterator(self)->map)->data, &as_MapIterator(self)->i))
        Exception_throw(Exception_new_stopIteration(es));

    Object *value = std_map_iterator_key(&as_MapIterator(self)->i);

    std_map_iterator_next(&as_MapIterator(self)->i);

    return value;
}

Object *Map_iterator(Esther *es, Object *self) {
    return MapIterator_new(es, self);
}

Object *Map_reversed(Esther *es, Object *self) {
    return MapIterator_new(es, self);
}
