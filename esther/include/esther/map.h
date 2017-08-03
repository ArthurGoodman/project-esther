#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Map {
    Object base;

    struct std_map *data;
} Map;

#define as_Map(obj) ((Map *) (obj))

Object *Map_new(Esther *es);

void Map_init(Esther *es, Object *self);

size_t Map_size(Object *self);

bool Map_contains(Object *self, Object *key);
Object *Map_get(Object *self, Object *key);
void Map_set(Object *self, Object *key, Object *value);

Object *Map_virtual_inspect(Esther *es, Object *self);

void Map_virtual_mapOnRefs(Mapper *self, MapFunction f);
void Map_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
