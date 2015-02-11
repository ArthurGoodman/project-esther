#include "call.h"

namespace esther {

Call::Call(Context *context, Tuple *args)
    : context(context), args(args) {
}

Context *Call::getContext() {
    return context;
}

Tuple *Call::getArgs() {
    return args;
}
}
