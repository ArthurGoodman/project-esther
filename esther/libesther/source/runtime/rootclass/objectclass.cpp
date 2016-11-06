#include "objectclass.h"

void ObjectClass::setupMethods() {
}

ObjectClass::ObjectClass(Runtime *runtime)
    : RootClass(runtime, "Object", nullptr) {
}
