#include "esther/id.h"

#include "esther/std_map.h"

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
