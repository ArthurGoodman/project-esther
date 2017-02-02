#pragma once

#include <functional>

#include "runtime/function.h"

class NativeFunction : public Function {
    typedef std::function<Ptr<Object>(Esther *, Ptr<Object>, const std::vector<Ptr<Object>> &)> FunctionBody;

    FunctionBody *body;

public:
    NativeFunction(Esther *esther, const std::string &name, int arity, const FunctionBody &body);

    void finalize() override;
    virtual int getSize() const override;

protected:
    Ptr<Object> execute(Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) override;
};
