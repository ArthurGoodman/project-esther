#include "esther/id.h"

#include "esther/std_map.h"
#include "esther/std_string.h"

static struct std_map *idString;
static struct std_map *stringId;

static ID nextId;

bool is_valid_id(ID id) {
    return id < nextId;
}

struct string id_to_str(ID id) {
    return is_valid_id(id) ? *(struct string *) std_map_get(idString, (void *) id) : string_null();
}

ID str_to_id(struct string str) {
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

    return (ID) std_map_get(stringId, &str);
}

ID c_str_to_id(const char *str) {
    return str_to_id(string_const(str));
}
