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
    Object_init(es, self, TObject, Esther_getRootObject(es, cstr_to_id("Range")));

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
