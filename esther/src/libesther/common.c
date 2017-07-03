#include "esther/common.h"

size_t ceilToPowerOf2(size_t n) {
    return 1 << (sizeof(n) * 8 - __builtin_clz(n - 1));
}
