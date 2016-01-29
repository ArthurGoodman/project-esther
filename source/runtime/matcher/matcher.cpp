#include "matcher.h"

#include "runtime.h"
#include "patternblock.h"
#include "signature.h"

Matcher::Matcher(std::list<Case *> cases)
    : Function("Matcher", "", Runtime::getRoot(), new Signature("Boolean", {"Object"}), new PatternBlock(cases)) {
}
