#pragma once

#include <string>

class Exception {
public:
    virtual ~Exception();

    virtual std::string message();
    virtual void raise() = 0;
};
