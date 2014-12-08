#pragma once
#include <common.h>

#include "object.h"

namespace Esther {

class ExpressionManager;
class Context;
class Node;

class Expression : public Object {
    friend class EstherEngine;
    friend class ExpressionManager;

    static ExpressionManager *manager;

    Node *node;

public:
    Object *eval(Context *context);
};
}
