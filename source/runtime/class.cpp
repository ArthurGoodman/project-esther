#include "class.h"

#include "runtime.h"
#include "tuple.h"
#include "method.h"
#include "nativemethod.h"
#include "nativeblock.h"

Class::Class(string name, Class *superclass)
    : Object("Class"), name(name), superclass(superclass) {
}

Class::Class(string name, string superclassName)
    : Object("Class"), name(name), superclass((Class *)Runtime::getRootClass(superclassName)) {
}

Class::Class(string name)
    : Object("Class"), name(name), superclass(Runtime::getObjectClass()) {
}

string Class::getName() {
    return name;
}

Class *Class::getSuperclass() {
    return superclass;
}

void Class::setSuperclass(Class *superclass) {
    this->superclass = superclass;
}

bool Class::isChild(Class *_class) {
    return false;
}

Object *Class::newInstance() {
    return new Object(this);
}

bool Class::hasMethod(string name) {
    return methods.find(name) != methods.end();
}

Method *Class::getMethod(string name) {
    return hasMethod(name) ? methods.at(name) : 0;
}

void Class::setMethod(Method *method) {
    methods[method->getName()] = method;
}

void Class::setMethod(string name, function<Object *(Object *, Tuple *)> body) {
    methods[name] = new NativeMethod(name, new NativeBlock(body));
}

Method *Class::lookup(string name) {
    if (hasMethod(name))
        return getMethod(name);

    if (superclass)
        return superclass->lookup(name);

    return 0;
}

Object *Class::call(string name, Tuple *args) {
    return Object::call(name, args);
}

Object *Class::call(string name, Object *arg) {
    return call(name, new Tuple(list<Object *>(1, arg)));
}

Object *Class::call(string name) {
    return call(name, new Tuple(list<Object *>()));
}

string Class::toString() {
    return name.empty() ? "<anonymous class>" : name;
}
