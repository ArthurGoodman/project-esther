#include "interface.h"

#include "runtime.h"

Interface::Interface(string name)
    : Class(name) {
}

Object *Interface::newInstance() {
    Runtime::runtimeError("cannot create new instance of an abstract class");
    return 0;
}

string Interface::toString() {
    return name.empty() ? "<anonymous interface>" : name;
}
