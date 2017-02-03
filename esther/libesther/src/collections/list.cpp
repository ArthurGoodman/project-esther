#include "collections/list.h"

namespace es {

template <class T>
List<T>::List()
    : size(0)
    , first(0)
    , last(0) {
}
}
