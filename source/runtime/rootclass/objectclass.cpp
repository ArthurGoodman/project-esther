#include "objectclass.h"

int memcmp(const void *ptr1, const void *ptr2, size_t num);
void *memset(void *ptr, int value, size_t num);
#include <windows.h>

#include "runtime.h"
#include "nativemethod.h"
#include "nativeblock.h"
#include "tuple.h"
#include "io.h"
#include "signature.h"
#include "string.h"
#include "iengine.h"
#include "utility.h"
#include "integer.h"

ObjectClass::ObjectClass()
    : RootClass("Object", 0) {
}

void ObjectClass::setupMethods() {
    auto classMethod = [](Object *self, Tuple *) -> Object * {
        return self->getClass();
    };

    setMethod("class", new Signature, classMethod);

    auto printMethod = [](Object *self, Tuple *args) -> Object * {
        if (args->isEmpty())
            IO::print(self->toString());
        else
            for (Object *o : *args)
                IO::print(o->toString());

        return Runtime::getNull();
    };

    setMethod("print", new Signature("Object", {}, true), printMethod);

    auto scanMethod = [](Object *, Tuple *) -> Object * {
        return new String(IO::scan());
    };

    setMethod("scan", new Signature("String", {}), scanMethod);

    auto scanLineMethod = [](Object *, Tuple *) -> Object * {
        return new String(IO::scanLine());
    };

    setMethod("scanLine", new Signature("String", {}), scanLineMethod);

    auto equalsMethod = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(self->immediateEquals(args->at(0)));
    };

    setMethod("equals", new Signature("Boolean", {"Object"}), equalsMethod);

    auto toStringMethod = [](Object *self, Tuple *) -> Object * {
        return new String(self->immediateToString());
    };

    setMethod("toString", new Signature("String", {}), toStringMethod);

    auto equalsOperator = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(self->equals(args->at(0)));
    };

    setMethod("==", new Signature("Boolean", {"Object"}), equalsOperator);

    auto notEqualsOperator = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(!self->equals(args->at(0)));
    };

    setMethod("!=", new Signature("Boolean", {"Object"}), notEqualsOperator);

    auto isMethod = [](Object *self, Tuple *args) -> Object * {
        return Runtime::toBoolean(self->is((Class *)args->at(0)));
    };

    setMethod("is", new Signature("Boolean", {"Class"}), isMethod);

    auto asMethod = [](Object *self, Tuple *args) -> Object * {
        return self->as((Class *)args->at(0));
    };

    setMethod("as", new Signature("Object", {"Class"}), asMethod);

    auto evalMethod = [](Object *, Tuple *args) -> Object * {
        return IEngine::instance()->run(((ValueObject *)args->at(0))->toString()); // TODO: Need to use proper context.
    };

    setMethod("eval", new Signature("Object", {"String"}), evalMethod);

    auto cloneMethod = [](Object *self, Tuple *) -> Object * {
        return self->clone();
    };

    setMethod("clone", new Signature("Object", {}), cloneMethod);

    auto systemMethod = [](Object *, Tuple *args) -> Object * {
        system(((String *)args->at(0))->toString().data());
        return Runtime::getNull();
    };

    setMethod("system", new Signature("Object", {"String"}), systemMethod);

    auto sleepMethod = [](Object *, Tuple *args) -> Object * {
        Sleep(((Integer *)args->at(0))->getVariant().toInteger());
        return Runtime::getNull();
    };

    setMethod("sleep", new Signature("Object", {"Integer"}), sleepMethod);

    auto setConsoleCursorPositionMethod = [](Object *, Tuple *args) -> Object * {
        COORD p = {(short)((Integer *)args->at(0))->getVariant().toInteger(), (short)((Integer *)args->at(1))->getVariant().toInteger()};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
        return Runtime::getNull();
    };

    setMethod("setConsoleCursorPosition", new Signature("Object", {"Integer", "Integer"}), setConsoleCursorPositionMethod);
}

Object *ObjectClass::createNewInstance() {
    return new Object;
}
