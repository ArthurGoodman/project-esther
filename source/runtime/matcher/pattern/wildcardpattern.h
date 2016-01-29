#pragma once

#include "pattern.h"

class WildcardPattern : public Pattern {
public:
    bool match(IObject *object);
};
