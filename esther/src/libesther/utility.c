#include "esther/utility.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __linux
#include <windows.h>
#endif

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

    if (fread(str.data, 1, size, file) != size)
        return string_null();

    str.data[size] = '\0';
    str.size = size;

    fclose(file);

    return str;
}

const char *full_path(const char *path) {
    char buffer[PATH_MAX];

#ifdef __linux
    if (realpath(path, buffer)) {
    }
#else
    GetFullPathNameA(path, PATH_MAX, buffer, NULL);
#endif

    return strdup(buffer);
}
