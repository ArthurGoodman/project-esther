#pragma once

#include <string>

#include "common/common.h"

#if HEAP_VARIANT

class VariantPrivate;

class Variant {
    VariantPrivate *data;

public:
    enum Type {
        Null,
        Integer,
        Real,
        Char,
        String
    };

public:
    Variant();
    Variant(int value);
    Variant(double value);
    Variant(char value);
    Variant(const std::string &value);
    Variant(const char *value);

    Variant(const Variant &v);
    Variant(Variant &&v);

    Variant &operator=(const Variant &v);
    Variant &operator=(Variant &&v);

    ~Variant();

    Type getType() const;

    int toInteger() const;
    double toReal() const;
    char toChar() const;
    std::string toString() const;

    bool isNull() const;
};

#else

class Variant {
public:
    enum Type {
        Null,
        Char,
        Integer,
        Real,
        String
    };

private:
    Type type;

    union {
        char character;
        int integer;
        double real;
        char *string;
    };

public:
    Variant();
    Variant(char value);
    Variant(int value);
    Variant(double value);
    Variant(const std::string &value);
    Variant(const char *value);

    Variant(const Variant &v);
    Variant(Variant &&v);

    Variant &operator=(const Variant &v);
    Variant &operator=(Variant &&v);

    Type getType() const;

    Variant convertTo(Type type) const;

    char toChar() const;
    int toInteger() const;
    double toReal() const;
    std::string toString() const;

    bool isNull() const;

    Variant operator+(const Variant &v) const;
    Variant operator-(const Variant &v) const;
    Variant operator*(const Variant &v) const;
    Variant operator/(const Variant &v) const;
    Variant operator%(const Variant &v) const;
    Variant pow(const Variant &v) const;

    bool operator<(const Variant &v) const;
    bool operator<=(const Variant &v) const;
    bool operator>(const Variant &v) const;
    bool operator>=(const Variant &v) const;
    bool operator==(const Variant &v) const;
    bool operator!=(const Variant &v) const;

private:
    static std::pair<Variant, Variant> coerce(const Variant &a, const Variant &b);
};

#endif
