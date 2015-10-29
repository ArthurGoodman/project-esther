#include "patternblock.h"

#include "runtime.h"
#include "case.h"
#include "pattern.h"
#include "matchfailureexception.h"
#include "context.h"

PatternBlock::PatternBlock(list<Case *> cases)
    : cases(cases) {
}

Object *PatternBlock::eval(Context *) {
    Runtime::runtimeError("cannot evaluate native code block without its function");
    return 0;
}

Object *PatternBlock::eval(Object *object, Context *context) {
    Object *value = 0;

    for (Case *c : cases)
        if ((value = c->match(object, context->childContext())))
            return value;

    throw new MatchFailureException;
}
