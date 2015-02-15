#pragma once
#include "common.h"

#include "pattern.h"

class WildcardPattern : public Pattern {
public:
    bool match(Object *object);
};
