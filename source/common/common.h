#pragma once
#include <string>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <functional>
#include <memory>
using namespace std;

template <class A, class B>
list<B> &operator<<(list<B> &l, const A &e) {
    l.push_back((B)e);
    return l;
}

template <class A, class B>
list<B> *operator<<(list<B> *l, const A &e) {
    l->push_back((B)e);
    return l;
}

template <class A, class B>
vector<B> &operator<<(vector<B> &v, const A &e) {
    v.push_back((B)e);
    return v;
}

template <class A, class B>
vector<B> *operator<<(vector<B> *v, const A &e) {
    v->push_back((B)e);
    return v;
}
