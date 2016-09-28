#pragma once

#include "object.h"
#include "context.h"

class Function : public Object {
    std::string name;
    Context *context;

public:
    void setContext(Context *context);
};
