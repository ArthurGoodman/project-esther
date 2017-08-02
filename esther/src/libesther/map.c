#include "esther/map.h"

#include <string.h>

#include "esther/esther.h"
#include "esther/std_map.h"
#include "esther/string.h"

Object *Map_new(Esther *es) {
    Object *self = gc_alloc(sizeof(Map));
    Map_init(es, self);
    return self;
}

static ObjectVTable vtable_for_Map = {
    .base = {
        .base = {
            .mapOnRefs = Map_virtual_mapOnRefs },
        .finalize = Map_virtual_finalize },
    .toString = Map_virtual_inspect,
    .inspect = Map_virtual_inspect,
    .equals = Object_virtual_equals,
    .less = Object_virtual_less,
    .isTrue = Object_virtual_isTrue
};

void Map_init(Esther *es, Object *self) {
    Object_init(es, self, TMap, Esther_getRootObject(es, c_str_to_id("Map")));

    as_Map(self)->data = std_map_new(compare_obj);

    *(void **) self = &vtable_for_Map;
}

size_t Map_size(Object *self) {
    return std_map_size(as_Map(self)->data);
}

bool Map_contains(Object *self, Object *key) {
    return std_map_contains(as_Map(self)->data, key);
}

Object *Map_get(Object *self, Object *key) {
    return std_map_get(as_Map(self)->data, key);
}

void Map_set(Object *self, Object *key, Object *value) {
    std_map_set(as_Map(self)->data, key, value);
}

Object *Map_virtual_inspect(Esther *es, Object *self) {
    struct std_map *data = as_Map(self)->data;
    size_t size = std_map_size(data);

    Object *str = String_new_c_str(es, "[");

    std_map_iterator i;
    std_map_begin(data, &i);

    size_t index = 0;

    while (!std_map_end(data, &i)) {
        String_append(str, Object_inspect(es, std_map_iterator_key(&i)));
        String_append_c_str(str, " => ");
        String_append(str, Object_inspect(es, std_map_iterator_value(&i)));

        if (index++ < size - 1)
            String_append_c_str(str, ", ");

        std_map_iterator_next(&i);
    }

    String_append_c_str(str, "]");

    return str;
}

void Map_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    Object_virtual_mapOnRefs(self, f);

    std_map_iterator i;
    std_map_begin(as_Map(self)->data, &i);

    while (!std_map_end(as_Map(self)->data, &i)) {
        f(std_map_iterator_key(&i));
        f(std_map_iterator_value(&i));
        std_map_iterator_next(&i);
    }
}

void Map_virtual_finalize(ManagedObject *self) {
    Object_virtual_finalize(self);

    std_map_delete(as_Map(self)->data);
}
