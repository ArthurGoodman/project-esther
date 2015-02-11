#include "callstack.h"

namespace esther {

stack<Call *> CallStack::calls;

void CallStack::beginCall(Call *call) {
    calls.push(call);
}

void CallStack::endCall() {
    calls.pop();
}

Call *CallStack::current() {
    return calls.top();
}
}
