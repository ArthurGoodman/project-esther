#include "esther/std_map.h"

#include <map>
#include <string>

namespace {
typedef std::map<void *, void *, Compare> cpp_map;

inline std_map *to_c(cpp_map *ptr) {
    return reinterpret_cast<std_map *>(ptr);
}

inline cpp_map *to_cpp(std_map *ptr) {
    return reinterpret_cast<cpp_map *>(ptr);
}
}

std_map *std_map_new(Compare compare) {
    return to_c(new cpp_map(compare));
}

void std_map_delete(std_map *map) {
    delete to_cpp(map);
}

bool std_map_contains(std_map *map, const void *key) {
    return to_cpp(map)->find((void *)key) != to_cpp(map)->end();
}

void *std_map_get(std_map *map, const void *key) {
    return (*to_cpp(map))[(void *)key];
}

void std_map_set(std_map *map, const void *key, void *value) {
    (*to_cpp(map))[(void *)key] = value;
}

void std_map_begin(std_map *map, std_map_iterator *i) {
    *reinterpret_cast<cpp_map::iterator *>(i) = to_cpp(map)->begin();
}

bool std_map_end(std_map *map, std_map_iterator *i) {
    return *reinterpret_cast<cpp_map::iterator *>(i) == to_cpp(map)->end();
}

void *std_map_iterator_key(std_map_iterator *i) {
    return (*reinterpret_cast<cpp_map::iterator *>(i))->first;
}

void *std_map_iterator_value(std_map_iterator *i) {
    return (*reinterpret_cast<cpp_map::iterator *>(i))->second;
}

void std_map_iterator_set_value(std_map_iterator *i, void *value) {
    (*reinterpret_cast<cpp_map::iterator *>(i))->second = value;
}

void std_map_iterator_next(std_map_iterator *i) {
    ++(*reinterpret_cast<cpp_map::iterator *>(i));
}
