#include "str.h"

#include <string>

namespace {
inline struct string *to_c(std::string *ptr) {
    return reinterpret_cast<struct string *>(ptr);
}

inline std::string *to_cpp(struct string *ptr) {
    return reinterpret_cast<std::string *>(ptr);
}
}

struct string *string_new() {
    return to_c(new std::string());
}

string *string_new_c_str(const char *str) {
    return to_c(new std::string(str));
}

void string_delete(struct string *str) {
    delete to_cpp(str);
}

struct string *string_append(struct string *self, struct string *str) {
    to_cpp(self)->append(*to_cpp(str));
    return self;
}

struct string *string_append_c_str(struct string *self, const char *str) {
    to_cpp(self)->append(str);
    return self;
}

size_t string_size(string *self) {
    return to_cpp(self)->size();
}

char string_at(string *self, size_t i) {
    return to_cpp(self)->at(i);
}

const char *string_c_str(string *self) {
    return to_cpp(self)->c_str();
}
