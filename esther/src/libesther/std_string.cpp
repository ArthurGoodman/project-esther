#include "esther/std_string.h"

#include <cstdarg>
#include <cstring>
#include <string>
#include <vector>

namespace {
inline std_string *to_c(std::string *ptr) {
    return reinterpret_cast<std_string *>(ptr);
}

inline std::string *to_cpp(std_string *ptr) {
    return reinterpret_cast<std::string *>(ptr);
}

std_string *vformat(const char *fmt, va_list ap) {
    size_t size = 1024;
    char stackbuf[size];

    std::vector<char> dynamicbuf;
    char *buf = &stackbuf[0];
    va_list ap_copy;

    while (true) {
        va_copy(ap_copy, ap);
        int needed = vsnprintf(buf, size, fmt, ap);
        va_end(ap_copy);

        if (needed <= static_cast<int>(size) && needed >= 0)
            return std_string_new_init(buf);

        size = needed > 0 ? needed + 1 : size * 2;
        dynamicbuf.resize(size);
        buf = &dynamicbuf[0];
    }
}
}

std_string *std_string_new() {
    return to_c(new std::string());
}

std_string *std_string_new_init(const char *str) {
    return to_c(new std::string(str));
}

void std_string_delete(std_string *self) {
    delete to_cpp(self);
}

std_string *std_string_append(std_string *self, std_string *str) {
    to_cpp(self)->append(*to_cpp(str));
    return self;
}

std_string *std_string_append_c_str(std_string *self, const char *str) {
    to_cpp(self)->append(str);
    return self;
}

std_string *std_string_append_char(std_string *self, char c) {
    to_cpp(self)->append(1, c);
    return self;
}

size_t std_string_size(std_string *self) {
    return to_cpp(self)->size();
}

bool std_string_isEmpty(std_string *self) {
    return to_cpp(self)->empty();
}

bool std_string_equals(std_string *self, std_string *str) {
    return *to_cpp(self) == *to_cpp(str);
}

bool std_string_contains(std_string *self, char c) {
    return to_cpp(self)->find(c) != std::string::npos;
}

char std_string_at(std_string *self, size_t index) {
    return to_cpp(self)->at(index);
}

const char *std_string_c_str(std_string *self) {
    return to_cpp(self)->c_str();
}

std_string *std_string_format(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    std_string *str = vformat(fmt, ap);
    va_end(ap);
    return str;
}

std_string *std_string_format_va(const char *fmt, va_list ap) {
    return vformat(fmt, ap);
}