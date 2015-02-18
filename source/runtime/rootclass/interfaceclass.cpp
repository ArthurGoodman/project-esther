#include "interfaceclass.h"

#include "interface.h"

InterfaceClass::InterfaceClass()
    : RootClass("Interface") {
}

Object *InterfaceClass::newInstance() {
    return new Interface("");
}

void InterfaceClass::setupMethods() {
}
