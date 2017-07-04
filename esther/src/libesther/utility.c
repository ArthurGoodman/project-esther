#include "esther/utility.h"

#include <stdio.h>
#include <stdlib.h>

#include "esther/std_string.h"

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
