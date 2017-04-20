#include "strmap.h"

#include <map>
#include <string>

#define to_c(ptr) (reinterpret_cast<struct strmap *>(ptr))
#define to_cpp(ptr) (reinterpret_cast<std::map<std::string, void *> *>(ptr))

struct strmap *strmap_new() {
    return to_c((new std::map<std::string, void *>));
}

void strmap_delete(struct strmap *map) {
    delete to_cpp(map);
}

bool strmap_contains(struct strmap *map, const char *str) {
    return to_cpp(map)->find(str) != to_cpp(map)->end();
}

void *strmap_get(struct strmap *map, const char *str) {
    return (*to_cpp(map))[str];
}

void strmap_set(struct strmap *map, const char *str, void *val) {
    (*to_cpp(map))[str] = val;
}
