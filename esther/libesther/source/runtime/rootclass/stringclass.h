#pragma once

#include "rootclass.h"

class ValueObject;

class StringClass : public RootClass {
    friend class Esther;

public:
    ValueObject *createString(const std::string &value);

protected:
    Object *createNewInstance(const std::vector<Object *> &args);

    void setupMethods();

private:
    StringClass(Esther *e);
};
