#pragma once

#include <string>

class Object {
public:
    virtual ~Object();

    std::string toString() const;
};
