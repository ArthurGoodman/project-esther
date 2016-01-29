#include "nativeblock.h"

#include "runtime.h"

NativeBlock::NativeBlock(std::function<IObject *(IObject *, Tuple *)> body)
    : body(body) {
}

IObject *NativeBlock::eval(Context *) {
    Runtime::runtimeError("cannot evaluate native code block without its function");
    return 0;
}

IObject *NativeBlock::eval(IObject *self, Tuple *args) {
    return body(self, args);
}

IObject *NativeBlock::clone() {
    return new NativeBlock(body);
}
