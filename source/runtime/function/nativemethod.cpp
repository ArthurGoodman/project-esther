#include "nativemethod.h"

#include "runtime.h"
#include "nativeblock.h"
#include "signature.h"

NativeMethod::NativeMethod(string className, string name, Context *context, Signature *signature, NativeBlock *body, Object *self, bool staticFlag)
    : Method(className, name, context, signature, body, self, staticFlag) {
}

NativeMethod::NativeMethod(string name, Signature *signature, NativeBlock *body, Object *self, bool staticFlag)
    : Method(name, Runtime::getRoot(), signature, body, self, staticFlag) {
}

Object *NativeMethod::execute(Object *self, Tuple *args) {
    return ((NativeBlock *)body)->eval(self, args);
}
