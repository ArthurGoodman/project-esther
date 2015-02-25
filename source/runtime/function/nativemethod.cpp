#include "nativemethod.h"

#include "runtime.h"
#include "nativeblock.h"
#include "signature.h"

NativeMethod::NativeMethod(string name, Signature *signature, NativeBlock *body, Object *self, bool isStatic)
    : Method(name, Runtime::getRoot(), signature, body, self, isStatic) {
}

Object *NativeMethod::execute(Object *self, Tuple *args) {
    return ((NativeBlock *)body)->eval(self, args);
}
