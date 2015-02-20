#include "method.h"

Method::Method(string name, Context *context, Signature *signature, Block *body)
    : Function("Method", name, context, signature, body) {
}

Object *Method::invoke(Object *self, Tuple *args) {
    return Function::invoke(self, args);
}

string Method::toString() {
    return name.empty() ? "<anonymous method>" : "<method " + name + ">";
}

void Method::check(Object *self, Tuple *args) {
    return Function::check(self, args);
}
