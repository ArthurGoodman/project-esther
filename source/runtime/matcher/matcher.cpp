#include "matcher.h"

#include "runtime.h"
#include "patternblock.h"

Matcher::Matcher(list<Case *> cases)
    : Function("Matcher", "", Runtime::getRoot(), {}, new PatternBlock(cases)) {
}
