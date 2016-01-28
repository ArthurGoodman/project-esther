#include "class.h"

#include "runtime.h"
#include "tuple.h"
#include "method.h"
#include "overloadedmethod.h"
#include "signature.h"

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
    return superclass ? superclass : (Class *)Runtime::getNull();
}

void Class::setSuperclass(Class *superclass) {
    this->superclass = superclass;
}

bool Class::isChild(Class *_class) {
    return this == _class || (superclass ? (superclass == _class ? true : superclass->isChild(_class)) : false);
}

IObject *Class::newInstance() {
    return newInstance(new Tuple({}));
}

IObject *Class::newInstance(Tuple *args) {
    IObject *instance = createNewInstance();

    if (lookup("initialize"))
        instance->call("initialize", args);
    else if (args->size() > 0)
        Runtime::runtimeError("'initialize' method doesn't exist");

    return instance;
}

bool Class::hasMethod(string name) {
    return hasAttribute(name) && dynamic_cast<Method *>(getAttribute(name));
}

Method *Class::getMethod(string name) {
    return hasMethod(name) ? (Method *)getAttribute(name) : 0;
}

void Class::setMethod(Method *method) {
    setMethod(method->getName(), method);
}

void Class::setMethod(string name, Method *method) {
    if (hasMethod(name)) {
        Method *existing = getMethod(name);

        if (existing->isStatic() == method->isStatic() && existing->getSelf() == method->getSelf()) {
            if (existing->getSignature()->weakEquals(method->getSignature())) {
                if (dynamic_cast<OverloadedMethod *>(existing))
                    ((OverloadedMethod *)existing)->replaceMethod(method);
                else
                    setAttribute(name, method);
            } else if (dynamic_cast<OverloadedMethod *>(existing)) {
                OverloadedMethod *overloadedMethod = (OverloadedMethod *)existing;
                overloadedMethod->addMethod(method);
            } else {
                OverloadedMethod *newMethod = new OverloadedMethod(name, method->getSelf(), method->isStatic());
                newMethod->addMethod(existing);
                newMethod->addMethod(method);

                setAttribute(name, newMethod);
            }

            return;
        }
    }

    setAttribute(name, method);
}

IObject *Class::lookup(string name) {
    if (hasAttribute(name))
        return getAttribute(name);

    if (superclass)
        return superclass->lookup(name);

    return 0;
}

IObject *Class::call(string name, Tuple *args) {
    if (hasMethod(name)) {
        Method *m = getMethod(name);

        if (m->isStatic())
            return m->invoke(this, args);
    }

    return Object::call(name, args);
}

string Class::toString() {
    return name.empty() ? "<anonymous class>" : name;
}

IObject *Class::createNewInstance() {
    return new Object(this);
}
