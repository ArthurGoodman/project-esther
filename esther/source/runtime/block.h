#pragma once

class Object;
class Context;

class Block {
public:
    virtual ~Block();

    virtual Object *eval(Context *context) = 0;
};
