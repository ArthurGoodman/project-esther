#include "iobject.h"

#include "tuple.h"

IObject::~IObject() {
}

IObject *IObject::call(const std::string &name, IObject *arg) {
    return call(name, new Tuple(std::list<IObject *>(1, arg)));
}

IObject *IObject::call(const std::string &name) {
    return call(name, new Tuple(std::list<IObject *>()));
}
