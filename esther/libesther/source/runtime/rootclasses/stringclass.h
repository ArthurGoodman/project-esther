#pragma once

#include "class.h"

class ValueObject;

class StringClass : public Class {
    friend class Runtime;

public:
    ValueObject *createString(const std::string &value);

protected:
    Object *createNewInstance();

private:
    StringClass(Class *objectClass);
};
