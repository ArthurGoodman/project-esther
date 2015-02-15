#include "nativeblock.h"

#include "runtime.h"

NativeBlock::NativeBlock(function<Object *(Object *, Tuple *)> body)
    : body(body) {
}

Object *NativeBlock::eval(Context *) {
    Runtime::runtimeError("cannot evaluate native code block without its function");
    return 0;
}

Object *NativeBlock::eval(Object *self, Tuple *args) {
    return body(self, args);
}
