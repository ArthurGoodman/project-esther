#include "esther/utility.h"

#include "esther/common.h"
#include "esther/std_string.h"

#ifndef __linux
#include <windows.h>
#endif

struct std_string *read_file(const char *fileName) {
    FILE *file = fopen(fileName, "rt");

    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(size + 1);

    if (fread(data, size, 1, file)) {
    }

    fclose(file);

    data[size] = '\0';

    struct std_string *str = std_string_new_init_len(data, size);

    free(data);

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

struct std_string *expand_tabs(const char *str, size_t length) {
    static const size_t tab_size = 4;

    struct std_string *result = std_string_new();

    for (size_t i = 0, c = 0; i < length; i++)
        if (str[i] == '\t') {
            size_t delta = c % tab_size ? c % tab_size : tab_size;
            c += delta;
            std_string_insert_char(result, std_string_size(result), delta, ' ');
        } else {
            std_string_append_char(result, str[i]);

            if (str[i] == '\n')
                c = 0;
            else
                c++;
        }

    return result;
}
