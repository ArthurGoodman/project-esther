#include "esther/id.h"

#include "esther/std_map.h"
#include "esther/std_string.h"

static struct std_map *idString = NULL;
static struct std_map *stringId = NULL;

static Id nextId = 0;

struct string id_to_str(Id id) {
    if (!idString || !std_map_contains(idString, (void *) id))
        return string_null();

    void *value = std_map_get(idString, (void *) id);

    return *((struct string *) &value);
}

Id str_to_id(struct string str) {
    if (!idString || !std_map_contains(stringId, str.data)) {
        if (!idString) {
            idString = std_map_new(compare_id);
            stringId = std_map_new(compare_str);
        }

        struct string newStr = string_copy(str);

        std_map_set(idString, (void *) nextId, newStr.data);
        std_map_set(stringId, newStr.data, (void *) nextId);

        return nextId++;
    }

    return (Id) std_map_get(stringId, str.data);
}

Id c_str_to_id(const char *str) {
    struct string tempStr = string_new_c_str(str);
    Id id = str_to_id(tempStr);
    string_free(&tempStr);
    return id;
}
