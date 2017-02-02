#pragma once

#include <functional>
#include <list>

#include "rootclass.h"

class Expression;
class Context;
class Function;

class FunctionClass : public RootClass {
public:
    FunctionClass(Esther *esther);

    void setupMethods(Esther *esther) override;

protected:
    Ptr<Object> createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &args) override;
};
