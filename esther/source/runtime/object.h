#pragma once

#include <string>

class Object {
public:
    Object();
    Object(const std::string &className);

    virtual ~Object();

    std::string toString() const;
};
