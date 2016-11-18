#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "common.h"

class Utility {
    static const int tabSize = 4;

public:
    template <class T>
    static std::string toString(T t, int base = 10, int precision = 16);

    template <class T>
    static T fromString(const std::string &str);

    static char toLower(char c);
    static char toUpper(char c);
    static bool isSpace(char c);
    static bool isSign(char c);
    static bool isDigit(char c);
    static bool isLetter(char c);
    static bool isLetterOrDigit(char c);

    static std::string expandTabs(const std::string &str);

    static uint ceilToPowerOf2(uint n);
};

template <class T>
std::string Utility::toString(T t, int base, int precision) {
    std::ostringstream s;

    s << std::setbase(base) << std::setprecision(precision) << t;

    return s.str();
}

template <class T>
T Utility::fromString(const std::string &str) {
    if (str.empty())
        return 0;

    std::istringstream s(str);

    T t;
    s >> t;

    return t;
}

template <>
inline double Utility::fromString<double>(const std::string &str) {
    if (str.empty())
        return 0;

    if (str == "inf")
        return INFINITY;

    if (str == "nan")
        return NAN;

    std::istringstream s(str);

    double t;
    s >> t;

    return t;
}
