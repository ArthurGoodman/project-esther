#include "iobject.h"

#include "tuple.h"

IObject::~IObject() {
}

IObject *IObject::call(string name, IObject *arg) {
    return call(name, new Tuple(list<IObject *>(1, arg)));
}

IObject *IObject::call(string name) {
    return call(name, new Tuple(list<IObject *>()));
}
