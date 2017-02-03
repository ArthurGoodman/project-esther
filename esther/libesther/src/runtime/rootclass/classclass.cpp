#include "classclass.h"

#include "runtime/esther.h"

ClassClass::ClassClass(Esther *esther)
    : RootClass(esther, "Class", nullptr) {
}

void ClassClass::setupMethods(Esther *esther) {
    Ptr<ClassClass> _this = this;

    _this->defFunc(esther, "new", -1, [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        return static_cast<Class *>(*self)->newInstance(esther, args);
    });

    _this->defFunc(esther, "superclass", [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &) -> Ptr<Object> {
        return static_cast<Class *>(*self)->getSuperclass() ? static_cast<Class *>(*self)->getSuperclass() : esther->getNull();
    });
}

Ptr<Object> ClassClass::createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &) {
    return new Class(esther, "", esther->getObjectClass());
}