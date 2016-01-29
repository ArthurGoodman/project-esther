#include "rootclass.h"

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"

RootClass::RootClass(const std::string &name, Class *superclass)
    : Class(name, superclass) {
    Runtime::setRootClass(this);
}

RootClass::RootClass(const std::string &name, const std::string &superclassName)
    : Class(name, superclassName) {
    Runtime::setRootClass(this);
}

RootClass::RootClass(const std::string &name)
    : Class(name) {
    Runtime::setRootClass(this);
}

void RootClass::setMethod(const std::string &name, Signature *signature, std::function<IObject *(IObject *, Tuple *)> body) {
    Class::setMethod(new NativeMethod(name, signature, new NativeBlock(body), this));
}

void RootClass::setStaticMethod(const std::string &name, Signature *signature, std::function<IObject *(IObject *, Tuple *)> body) {
    Class::setMethod(new NativeMethod(name, signature, new NativeBlock(body), this, true));
}
