#include "patternblock.h"

#include "runtime.h"
#include "case.h"
#include "pattern.h"
#include "matchfailureexception.h"

PatternBlock::PatternBlock(list<Case *> cases)
    : cases(cases) {
}

Object *PatternBlock::eval(Context *) {
    Runtime::runtimeError("cannot evaluate native code block without its function");
    return 0;
}

Object *PatternBlock::eval(Object *object) {
    foreach (i, cases)
        if ((*i)->getPattern()->match(object))
            return (*i)->match(object);

    throw new MatchFailureException;
}
