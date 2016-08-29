#pragma once

class Object;
class Context;

class Expression {
public:
    virtual ~Expression();

    virtual Object *eval(Context *context) = 0;
};
