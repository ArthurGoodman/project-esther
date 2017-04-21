#include "esther/std_string_map.h"

#include <map>
#include <string>

namespace {
inline struct std_string_map *to_c(std::map<std::string, void *> *ptr) {
    return reinterpret_cast<struct std_string_map *>(ptr);
}

inline std::map<std::string, void *> *to_cpp(struct std_string_map *ptr) {
    return reinterpret_cast<std::map<std::string, void *> *>(ptr);
}
}

struct std_string_map *std_string_map_new() {
    return to_c((new std::map<std::string, void *>));
}

void std_string_map_delete(struct std_string_map *map) {
    delete to_cpp(map);
}

bool std_string_map_contains(struct std_string_map *map, const char *str) {
    return to_cpp(map)->find(str) != to_cpp(map)->end();
}

void *std_string_map_get(struct std_string_map *map, const char *str) {
    return (*to_cpp(map))[str];
}

void std_string_map_set(struct std_string_map *map, const char *str, void *val) {
    (*to_cpp(map))[str] = val;
}
