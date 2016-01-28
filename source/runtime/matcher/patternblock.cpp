#include "patternblock.h"

#include "runtime.h"
#include "case.h"
#include "pattern.h"
#include "matchfailureexception.h"
#include "context.h"

PatternBlock::PatternBlock(list<Case *> cases)
    : cases(cases) {
}

IObject *PatternBlock::eval(Context *) {
    Runtime::runtimeError("cannot evaluate native code block without its function");
    return 0;
}

IObject *PatternBlock::eval(IObject *object, Context *context) {
    IObject *value = 0;

    for (Case *c : cases)
        if ((value = c->match(object, context->childContext())))
            return value;

    throw new MatchFailureException;
}
