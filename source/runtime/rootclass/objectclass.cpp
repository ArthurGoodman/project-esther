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
    auto classMethod = [](IObject *self, Tuple *) -> IObject * {
        return self->getClass();
    };

    setMethod("class", new Signature, classMethod);

    auto printMethod = [](IObject *self, Tuple *args) -> IObject * {
        if (args->isEmpty())
            IO::print(self->callToString());
        else
            for (IObject *o : *args)
                IO::print(o->callToString());

        return Runtime::getNull();
    };

    setMethod("print", new Signature("Object", {}, true), printMethod);

    auto scanMethod = [](IObject *, Tuple *) -> IObject * {
        return new String(IO::scan());
    };

    setMethod("scan", new Signature("String", {}), scanMethod);

    auto scanLineMethod = [](IObject *, Tuple *) -> IObject * {
        return new String(IO::scanLine());
    };

    setMethod("scanLine", new Signature("String", {}), scanLineMethod);

    auto equalsMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(self->equals(args->at(0)));
    };

    setMethod("equals", new Signature("Boolean", {"Object"}), equalsMethod);

    auto toStringMethod = [](IObject *self, Tuple *) -> IObject * {
        return new String(self->toString());
    };

    setMethod("toString", new Signature("String", {}), toStringMethod);

    auto equalsOperator = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(self->callEquals(args->at(0)));
    };

    setMethod("==", new Signature("Boolean", {"Object"}), equalsOperator);

    auto notEqualsOperator = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(!self->callEquals(args->at(0)));
    };

    setMethod("!=", new Signature("Boolean", {"Object"}), notEqualsOperator);

    auto isMethod = [](IObject *self, Tuple *args) -> IObject * {
        return Runtime::toBoolean(self->is((Class *)args->at(0)));
    };

    setMethod("is", new Signature("Boolean", {"Class"}), isMethod);

    auto asMethod = [](IObject *self, Tuple *args) -> IObject * {
        return self->as((Class *)args->at(0));
    };

    setMethod("as", new Signature("Object", {"Class"}), asMethod);

    auto evalMethod = [](IObject *, Tuple *args) -> IObject * {
        return IEngine::instance()->run(((ValueObject *)args->at(0))->callToString()); // TODO: Need to use proper context.
    };

    setMethod("eval", new Signature("Object", {"String"}), evalMethod);

    auto cloneMethod = [](IObject *self, Tuple *) -> IObject * {
        return self->clone();
    };

    setMethod("clone", new Signature("Object", {}), cloneMethod);

    auto systemMethod = [](IObject *, Tuple *args) -> IObject * {
        system(((String *)args->at(0))->callToString().data());
        return Runtime::getNull();
    };

    setMethod("system", new Signature("Object", {"String"}), systemMethod);

    auto sleepMethod = [](IObject *, Tuple *args) -> IObject * {
        Sleep(((Integer *)args->at(0))->getVariant().toInteger());
        return Runtime::getNull();
    };

    setMethod("sleep", new Signature("Object", {"Integer"}), sleepMethod);

    auto setConsoleCursorPositionMethod = [](IObject *, Tuple *args) -> IObject * {
        COORD p = {(short)((Integer *)args->at(0))->getVariant().toInteger(), (short)((Integer *)args->at(1))->getVariant().toInteger()};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
        return Runtime::getNull();
    };

    setMethod("setConsoleCursorPosition", new Signature("Object", {"Integer", "Integer"}), setConsoleCursorPositionMethod);
}

IObject *ObjectClass::createNewInstance() {
    return new Object;
}
