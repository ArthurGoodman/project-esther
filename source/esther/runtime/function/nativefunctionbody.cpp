#include "nativefunctionbody.h"

#include "runtime.h"
#include "callstack.h"
#include "call.h"
#include "context.h"

namespace esther {

NativeFunctionBody::NativeFunctionBody(function<Object *(Object *, Tuple *)> f)
    : f(f) {
}

Object *NativeFunctionBody::eval(Context *context) {
    Call *call = Runtime::getCallStack()->current();
    return f(context->getCurrentSelf(), call->getArgs());
}
}
