#include "utility.h"

#if defined(__linux)
#include <unistd.h>
#elif defined(__WIN32)
#include <windows.h>
#endif

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esther/std_string.h"

size_t ceil_to_power_of_2(size_t n) {
    return 1 << (sizeof(n) * 8 - __builtin_clz(n - 1));
}

struct string read_file(const char *fileName) {
    FILE *file = fopen(fileName, "rt");

    if (!file)
        return string_null();

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    struct string str = string_new_prealloc(size);

    if (fread(str.data, 1, size, file)) {
    }

    str.data[size] = '\0';
    str.size = size;

    fclose(file);

    return str;
}

const char *full_path(const char *path) {
    char buffer[PATH_MAX];

#if defined(__linux)
    if (realpath(path, buffer)) {
    }
#elif defined(__WIN32)
    GetFullPathNameA(path, PATH_MAX, buffer, NULL);
#endif

    return strdup(buffer);
}

struct string executable_dir() {
    struct string str = string_new_prealloc(PATH_MAX);

#if defined(__linux)
    char pathSeparator = '/';
    size_t len = readlink("/proc/self/exe", str.data, str.capacity);
#elif defined(__WIN32)
    char pathSeparator = '\\';
    size_t len = GetModuleFileNameA(GetModuleHandleW(NULL), str.data, str.capacity);
#endif

    if (len == (size_t) -1) {
        printf("error: unable to read executable location\n");
        return string_null();
    }

    str.size = len;

    string_erase(&str, string_rfind_char(str, pathSeparator, -1) + 1, -1);

    return str;
}
