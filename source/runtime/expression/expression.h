#pragma once
#include <common.h>

#include "object.h"

namespace esther {

class ExpressionManager;
class Context;
class Node;

class Expression : public Object {
    static ExpressionManager *manager;

    Node *node;

public:
    static void initialize();
    static void release();

    Object *eval(Context *context);
};
}
