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

#define forever while (true)

// Foreach loop for standart STL containters.
#define foreach (i, c) for (typeof(c.begin()) i = c.begin(); i != c.end(); ++i)

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

// String covertions:

template <class T>
string toString(T t, int precision = 16) {
    ostringstream s;
    s << setprecision(precision) << t;
    return s.str();
}

template <class T>
T fromString(string str) {
    istringstream s(str);
    T t;
    s >> t;
    return t;
}

template <>
inline double fromString<double>(string str) {
    if (str == "inf")
        return INFINITY;
    if (str == "nan")
        return NAN;
    istringstream s(str);
    double t;
    s >> t;
    return t;
}

// Basic character operations:

inline char toLower(char c) {
    return c < 'A' || c > 'Z' ? c : c + 'a' - 'A';
}

inline char toUpper(char c) {
    return c < 'a' || c > 'z' ? c : c + 'A' - 'a';
}

inline bool isSpace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

inline bool isSign(char c) {
    return c == '+' || c == '-';
}

inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

inline bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline bool isLetterOrDigit(char c) {
    return isLetter(c) || isDigit(c);
}

// Read the whole file into a string.
inline string readFile(string fileName) {
    ifstream f(fileName.data());

    if (!f) {
        cout << "error opening file '" << fileName << "'\n";
        return "";
    }

    ostringstream buffer;
    buffer << f.rdbuf();

    f.close();

    return buffer.str();
}
