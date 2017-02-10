#pragma once

#include <functional>

#include "runtime/function.h"

namespace es {

class NativeFunction : public Function {
    typedef std::function<Object *(Esther *, Object *volatile, const std::vector<Object *> &)> FunctionBody;

    FunctionBody body;

public:
    NativeFunction(Esther *esther, const std::string &name, int arity, const FunctionBody &body);

    void finalize() override;

protected:
    Object *execute(Esther *esther, Object *volatile self, const std::vector<Object *> &args) override;
};
}
