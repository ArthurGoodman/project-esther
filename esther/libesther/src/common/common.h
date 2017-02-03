#pragma once

#include <list>
#include <vector>

namespace es {

template <class A, class B>
std::list<B> &operator<<(std::list<B> &l, const A &e) {
    l.push_back(static_cast<B>(e));
    return l;
}

template <class A, class B>
std::list<B> *operator<<(std::list<B> *l, const A &e) {
    l->push_back(static_cast<B>(e));
    return l;
}

template <class A, class B>
std::vector<B> &operator<<(std::vector<B> &v, const A &e) {
    v.push_back(static_cast<B>(e));
    return v;
}

template <class A, class B>
std::vector<B> *operator<<(std::vector<B> *v, const A &e) {
    v->push_back(static_cast<B>(e));
    return v;
}
}
