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
using namespace std;

// Some useful functions and defines:

// Foreach loop for standart STL containters.
#define foreach(i, c) for (typeof(c.begin()) i = c.begin(); i != c.end(); ++i)

// Append operators:

template <class A, class B>
list<B> &operator<<(list<B> &l, const A &e) {
    l.push_back((B)e);
    return l;
}

// It is convenient sometimes not to dereference a pointer to a container:
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
