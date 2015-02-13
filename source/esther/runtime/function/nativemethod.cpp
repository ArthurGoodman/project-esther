#include "nativemethod.h"

#include "runtime.h"
#include "callstack.h"
#include "call.h"
#include "context.h"

namespace esther {

NativeMethod::NativeMethod(function<Object *(Object *, Tuple *)> f)
    : f(f) {
}

Object *NativeMethod::eval(Context *context) {
    Call *call = Runtime::getCallStack()->current();
    return f(context->getCurrentSelf(), call->getArgs());
}
}
