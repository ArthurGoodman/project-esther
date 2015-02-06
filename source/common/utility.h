#pragma once
#include "common.h"

class Utility {
public:
    // String covertions:

    template <class T>
    static string toString(T t, int base = 10, int precision = 16);

    template <class T>
    static T fromString(string str);

    // Basic character operations:

    static char toLower(char c);
    static char toUpper(char c);
    static bool isSpace(char c);
    static bool isSign(char c);
    static bool isDigit(char c);
    static bool isLetter(char c);
    static bool isLetterOrDigit(char c);
};

template <class T>
string Utility::toString(T t, int base, int precision) {
    ostringstream s;
    s << setbase(base) << setprecision(precision) << t;
    return s.str();
}

template <class T>
T Utility::fromString(string str) {
    istringstream s(str);
    T t;
    s >> t;
    return t;
}

template <>
inline double Utility::fromString<double>(string str) {
    if (str == "inf")
        return INFINITY;
    if (str == "nan")
        return NAN;
    istringstream s(str);
    double t;
    s >> t;
    return t;
}
