#pragma once

#include <string>

namespace es {

class Exception {
public:
    virtual ~Exception();

    virtual std::string message();
    virtual void raise() = 0;
};
}
