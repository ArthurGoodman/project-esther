#pragma once
#include "common.h"

namespace esther {

class Call;

class CallStack {
    static stack<Call *> calls;

public:
    static void beginCall(Call *call);
    static void endCall();

    static Call *current();
};
}
