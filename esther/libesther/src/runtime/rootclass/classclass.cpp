#include "runtime/rootclass/classclass.h"

#include "esther.h"

namespace es {

ClassClass::ClassClass(Esther *esther)
    : RootClass(esther, "Class", nullptr) {
}

void ClassClass::setupMethods(Esther *esther) {
    defFunc(esther, "new", -1, [](Esther *esther, Object *volatile self, const std::vector<Object *> &args) -> Object * {
        return static_cast<Class *volatile>(self)->newInstance(esther, args);
    });

    defFunc(esther, "superclass", [](Esther *esther, Object *volatile self, const std::vector<Object *> &) -> Object * {
        return static_cast<Class *volatile>(self)->getSuperclass() ? static_cast<Class *volatile>(self)->getSuperclass() : esther->getNull();
    });
}

Object *ClassClass::createNewInstance(Esther *esther, const std::vector<Object *> &) {
    return new Class(esther, "", esther->getObjectClass());
}
}
