#pragma once
#include "common.h"

#include "object.h"

namespace esther {

class Call;

class CallStack : public Object {
    static stack<Call *> calls;

public:
    static void beginCall(Call *call);
    static void endCall();

    static Call *current();
};
}
