#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Range {
    Object base;

    int64_t start, stop, step;
} Range;

#define as_Range(obj) ((Range *) (obj))

Object *Range_new(Esther *es, int64_t start, int64_t stop, int64_t step);

void Range_init(Esther *es, Object *self, int64_t start, int64_t stop, int64_t step);

Object *Range_getStart(Esther *es, Object *self);
Object *Range_getStop(Esther *es, Object *self);
Object *Range_getStep(Esther *es, Object *self);

#ifdef __cplusplus
}
#endif
