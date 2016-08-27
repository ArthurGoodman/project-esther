#pragma once

#include <list>
#include <vector>

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long ulong;

template <class A, class B>
std::list<B> &operator<<(std::list<B> &l, const A &e) {
    l.push_back((B)e);
    return l;
}

template <class A, class B>
std::list<B> *operator<<(std::list<B> *l, const A &e) {
    l->push_back((B)e);
    return l;
}

template <class A, class B>
std::vector<B> &operator<<(std::vector<B> &v, const A &e) {
    v.push_back((B)e);
    return v;
}

template <class A, class B>
std::vector<B> *operator<<(std::vector<B> *v, const A &e) {
    v->push_back((B)e);
    return v;
}
