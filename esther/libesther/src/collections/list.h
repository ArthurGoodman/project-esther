#pragma once

#include "memory/managedobject.h"

namespace es {

template <class T>
class List : public ManagedObject {
    class ListNode : public ManagedObject {
        T value;
        ListNode *next;
    };

    int size;
    ListNode *first, *last;

public:
    List();
};
}
