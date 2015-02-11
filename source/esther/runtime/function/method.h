#pragma once
#include "common.h"

#include "function.h"

namespace esther {

class Method : public Function {
public:
    Method(string name, Context *context, list<string> params, FunctionBody *body);

    Object *invoke(Object *self, Tuple *args);

//    string toString();
};
}
