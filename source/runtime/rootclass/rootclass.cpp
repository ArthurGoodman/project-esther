#include "rootclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"

RootClass::RootClass(string name, Class *superclass)
    : Class(name, superclass) {
    Runtime::setRootClass(this);
}

RootClass::RootClass(string name, string superclassName)
    : Class(name, superclassName) {
    Runtime::setRootClass(this);
}

RootClass::RootClass(string name)
    : Class(name) {
    Runtime::setRootClass(this);
}

void RootClass::setMethod(string name, Signature *signature, function<Object *(Object *, Tuple *)> body) {
    Class::setMethod(new NativeMethod(name, signature, new NativeBlock(body), this));
}

void RootClass::setStaticMethod(string name, Signature *signature, function<Object *(Object *, Tuple *)> body) {
    Class::setMethod(new NativeMethod(name, signature, new NativeBlock(body), this, true));
}
