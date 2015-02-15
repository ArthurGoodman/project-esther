#include "nativemethod.h"

#include "runtime.h"
#include "nativeblock.h"

NativeMethod::NativeMethod(string name, NativeBlock *body)
    : Method(name, Runtime::getRoot(), {}, body) {
}

Object *NativeMethod::invoke(Object *self, Tuple *args) {
    return ((NativeBlock *)body)->eval(self, args);
}
