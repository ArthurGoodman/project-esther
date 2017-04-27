#include "esther/id.h"

#include "esther/std_map.h"

Id id_empty;
Id id_brace;
Id id_class;
Id id_eq;
Id id_self;
Id id_attr;
Id id_new;
Id id_function;
Id id_call;
Id id_id;
Id id_sharp;
Id id_dot;

static struct std_map *idString = NULL;
static struct std_map *stringId = NULL;

static Id nextId = 0;

const char *idToString(Id id) {
    return idString && std_map_contains(idString, (const void *)id) ? std_map_get(idString, (const void *)id) : "";
}

Id stringToId(const char *str) {
    if (!idString || !std_map_contains(stringId, str)) {
        if (!idString) {
            idString = std_map_new(ulong_compare);
            stringId = std_map_new(string_compare);
        }

        const char *newStr = strdup(str);

        std_map_set(idString, (const void *)nextId, (void *)newStr);
        std_map_set(stringId, newStr, (void *)nextId);

        return nextId++;
    }

    return (Id)std_map_get(stringId, str);
}
