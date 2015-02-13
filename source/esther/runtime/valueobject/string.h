#pragma once
#include "common.h"

#include "valueobject.h"

namespace esther {

class String : public ValueObject {
public:
    String(string value);
    String(const char *value);
    String();
};
}
