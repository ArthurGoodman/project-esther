#include "objectclass.h"

void ObjectClass::setupMethods() {
}

ObjectClass::ObjectClass(Runtime *runtime, Class *objectClass)
    : RootClass(runtime, objectClass, "Object", nullptr) {
}
