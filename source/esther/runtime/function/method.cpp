#include "method.h"

namespace esther {

Method::Method(string name, Context *context, list<string> params, Block *body)
    : Function("Method", name, context, params, body) {
}

Object *Method::invoke(Object *self, Tuple *args) {
    return Function::invoke(self, args);
}

string Method::toString() {
    return name.empty() ? "<anonymous method>" : "<method " + name + ">";
}
}
