#include "nativemethod.h"

#include "runtime.h"
#include "nativeblock.h"
#include "signature.h"

NativeMethod::NativeMethod(string name, Signature *signature, NativeBlock *body)
    : Method(name, Runtime::getRoot(), signature, body) {
}

Object *NativeMethod::invoke(Object *self, Tuple *args) {
    check(self, args);

    return ((NativeBlock *)body)->eval(self, args);
}
