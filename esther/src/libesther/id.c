#include "esther/id.h"

#include "esther/std_map.h"
#include "esther/std_string.h"

static struct std_map *idString = NULL;
static struct std_map *stringId = NULL;

static Id nextId = 0;

struct string *id_to_str(Id id) {
    return idString && std_map_contains(idString, (void *) id) ? std_map_get(idString, (void *) id) : NULL;
}

Id str_to_id(const struct string str) {
    if (!idString || !std_map_contains(stringId, &str)) {
        if (!idString) {
            idString = std_map_new(compare_id);
            stringId = std_map_new(compare_str);
        }

        struct string *newStr = malloc(sizeof *newStr);
        *newStr = string_copy(str);

        std_map_set(idString, (void *) nextId, newStr);
        std_map_set(stringId, newStr, (void *) nextId);

        return nextId++;
    }

    return (Id) std_map_get(stringId, &str);
}

Id c_str_to_id(const char *str) {
    return str_to_id(string_new_const(str));
}
