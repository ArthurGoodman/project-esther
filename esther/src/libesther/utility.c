#include "esther/utility.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef __linux
#include <windows.h>
#endif

#include "esther/std_string.h"

bool isControlCharacter(char c) {
    return iscntrl(c) || c == '\\' || c == '\'' || c == '"';
}

size_t ceilToPowerOf2(size_t n) {
    return 1 << (sizeof(n) * 8 - __builtin_clz(n - 1));
}

struct string vformat(const char *fmt, va_list ap) {
    int size = 1024;
    char stackbuf[size];
    char *buf = stackbuf;
    char *dynamicbuf = NULL;

    while (true) {
        va_list ap_copy;
        va_copy(ap_copy, ap);
        int needed = vsnprintf(buf, size, fmt, ap_copy);
        va_end(ap_copy);

        if (needed <= size && needed >= 0) {
            struct string str = string_new(buf, needed);
            free(dynamicbuf);
            return str;
        }

        size = needed > 0 ? needed + 1 : size * 2;
        dynamicbuf = realloc(dynamicbuf, size);
        buf = dynamicbuf;
    }
}

struct string read_file(const char *fileName) {
    FILE *file = fopen(fileName, "rt");

    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(size + 1);

    if (fread(data, size, 1, file)) {
    }

    fclose(file);

    data[size] = '\0';

    struct string str = string_new(data, size);

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

struct string expand_tabs(const char *str, size_t length) {
    static const size_t tab_size = 4;

    struct string result = string_new_empty();

    for (size_t i = 0, c = 0; i < length; i++)
        if (str[i] == '\t') {
            size_t delta = c % tab_size ? c % tab_size : tab_size;
            c += delta;
            string_insert_char(&result, string_size(&result), ' ', delta);
        } else {
            string_append_char(&result, str[i]);

            if (str[i] == '\n')
                c = 0;
            else
                c++;
        }

    return result;
}
