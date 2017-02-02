#include "characterclass.h"

#include "runtime/valueobject.h"
#include "runtime/esther.h"
#include "runtime/rootclass/numericclass.h"
#include "runtime/nativefunction.h"
#include "common/utility.h"

CharacterClass::CharacterClass(Esther *esther)
    : RootClass(esther, "Character", esther->getRootClass("Numeric")) {
}

void CharacterClass::setupMethods(Esther *esther) {
    Ptr<CharacterClass> _this = this;

    _this->setAttribute("()", new NativeFunction(esther, "()", 2, [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
                            if (!dynamic_cast<CharacterClass *>(*self)) {
                                Esther::runtimeError("Character.(): invalid self");
                                return nullptr;
                            }

                            if (!dynamic_cast<ValueObject *>(*args[1])) {
                                Esther::runtimeError("Character.(): invalid argument");
                                return nullptr;
                            }

                            return new ValueObject(esther, ((ValueObject *)*args[1])->getVariant().toChar());
                        }));

    _this->defValueObjectFunc(esther, "initialize", -1, [](Esther *, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        if ((int)args.size() > 1)
            Esther::runtimeError("Character.initialize: invalid number of arguments");

        if (!args.empty())
            ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toChar());

        return self;
    });

    _this->defFunc(esther, "isSpace", [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &) -> Ptr<Object> {
        return esther->toBoolean(Utility::isSpace(((ValueObject *)*self)->getVariant().toChar()));
    });

    _this->defFunc(esther, "isDigit", [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &) -> Ptr<Object> {
        return esther->toBoolean(Utility::isDigit(((ValueObject *)*self)->getVariant().toChar()));
    });

    _this->defFunc(esther, "isLetter", [](Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &) -> Ptr<Object> {
        return esther->toBoolean(Utility::isLetter(((ValueObject *)*self)->getVariant().toChar()));
    });

    _this->defValueObjectFunc(esther, "=", 1, [](Esther *, Ptr<Object> self, const std::vector<Ptr<Object>> &args) -> Ptr<Object> {
        ((ValueObject *)*self)->setVariant(((ValueObject *)*args[0])->getVariant().toChar());
        return self;
    });
}

Ptr<Object> CharacterClass::createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &) {
    return new ValueObject(esther, '\0');
}
