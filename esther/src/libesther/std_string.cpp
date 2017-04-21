#include "esther/std_string.h"

#include <string>

namespace {
inline struct std_string *to_c(std::string *ptr) {
    return reinterpret_cast<struct std_string *>(ptr);
}

inline std::string *to_cpp(struct std_string *ptr) {
    return reinterpret_cast<std::string *>(ptr);
}
}

struct std_string *std_string_new() {
    return to_c(new std::string());
}

struct std_string *std_string_new_init(const char *str) {
    return to_c(new std::string(str));
}

void std_string_delete(struct std_string *str) {
    delete to_cpp(str);
}

struct std_string *std_string_append(struct std_string *self, struct std_string *str) {
    to_cpp(self)->append(*to_cpp(str));
    return self;
}

struct std_string *std_string_append_c_str(struct std_string *self, const char *str) {
    to_cpp(self)->append(str);
    return self;
}

size_t std_string_size(struct std_string *self) {
    return to_cpp(self)->size();
}

char std_string_at(struct std_string *self, size_t i) {
    return to_cpp(self)->at(i);
}

const char *std_string_c_str(struct std_string *self) {
    return to_cpp(self)->c_str();
}
