#include "nativeblock.h"

NativeBlock::NativeBlock(const std::function<Object *(const std::list<Object *> &)> &f)
    : f(f) {
}

Object *NativeBlock::eval(Context *context) {
    return 0;
}
