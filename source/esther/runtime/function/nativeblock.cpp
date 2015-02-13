#include "nativeblock.h"

#include "runtime.h"

namespace esther {

NativeBlock::NativeBlock(function<Object *(Object *, Tuple *)> body)
    : body(body) {
}

Object *NativeBlock::eval(Context *) {
    Runtime::runtimeError("cannot evaluate native code without its method");
    return 0;
}

Object *NativeBlock::eval(Object *self, Tuple *args) {
    return body(self, args);
}
}
