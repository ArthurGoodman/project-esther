#pragma once
#include "common.h"

#include "object.h"

namespace esther {

class Tuple : public Object {
    int n;
    Object **data;

public:
    Tuple(int size = 0);
    Tuple(list<Object *> data);

    int size() const;

    Object *&at(int i) const;
};
}
