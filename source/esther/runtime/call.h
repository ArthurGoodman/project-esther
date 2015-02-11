#pragma once
#include "common.h"

namespace esther {

class Context;
class Tuple;

class Call {
    Context *context;
    Tuple *args;

public:
    Call(Context *context, Tuple *args);

    Context *getContext();
    Tuple *getArgs();
};
}
