#include "esther/range.h"

#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/string.h"
#include "esther/valueobject.h"

Object *Range_new(Esther *es, int64_t start, int64_t stop, int64_t step) {
    Object *self = gc_alloc(sizeof(Range));
    Range_init(es, self, start, stop, step);
    return self;
}

void Range_init(Esther *es, Object *self, int64_t start, int64_t stop, int64_t step) {
    Object_init(es, self, TObject, Esther_getRootObject(es, c_str_to_id("Range")));

    as_Range(self)->start = start;
    as_Range(self)->stop = stop;
    as_Range(self)->step = step;

    *(void **) self = &vtable_for_Object;
}

Object *Range_getStart(Esther *es, Object *self) {
    return ValueObject_new_int(es, as_Range(self)->start);
}

Object *Range_getStop(Esther *es, Object *self) {
    return ValueObject_new_int(es, as_Range(self)->stop);
}

Object *Range_getStep(Esther *es, Object *self) {
    return ValueObject_new_int(es, as_Range(self)->step);
}

Object *Range_iterator(Esther *es, Object *self) {
    return RangeIterator_new(es, as_Range(self)->start, as_Range(self)->stop, as_Range(self)->step);
}

Object *RangeIterator_new(Esther *es, int64_t start, int64_t stop, int64_t step) {
    Object *self = gc_alloc(sizeof(Range));
    RangeIterator_init(es, self, start, stop, step);
    return self;
}

void RangeIterator_init(Esther *es, Object *self, int64_t start, int64_t stop, int64_t step) {
    Object_init(es, self, TObject, Esther_getRootObject(es, c_str_to_id("RangeIterator")));

    as_Range(self)->start = start;
    as_Range(self)->stop = stop;
    as_Range(self)->step = step;

    *(void **) self = &vtable_for_Object;
}

Object *RangeIterator_next(Esther *es, Object *self) {
    if (as_Range(self)->start == as_Range(self)->stop)
        Exception_throw(Exception_new_stopIteration(es));

    as_Range(self)->start += as_Range(self)->step;

    return ValueObject_new_int(es, as_Range(self)->start - as_Range(self)->step);
}
