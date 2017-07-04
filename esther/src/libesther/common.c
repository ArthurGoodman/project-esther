#include "esther/common.h"

size_t ceilToPowerOf2(size_t n) {
    return 1 << (sizeof(n) * 8 - __builtin_clz(n - 1));
}

struct string vformat(const char *fmt, va_list ap) {
    int size = 1 << 10;
    char stackbuf[size];
    char *buf = stackbuf;
    char *dynamicbuf = NULL;

    while (true) {
        va_list ap_copy;
        va_copy(ap_copy, ap);
        int needed = vsnprintf(buf, size, fmt, ap_copy);
        va_end(ap_copy);

        if (needed <= size && needed >= 0)
            return string_new(buf, needed);

        size = needed > 0 ? needed + 1 : size * 2;
        dynamicbuf = realloc(dynamicbuf, size);
        buf = dynamicbuf;
    }
}
