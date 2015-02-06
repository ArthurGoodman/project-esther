#pragma once
#include "common.h"

class VariantPrivate;

class Variant {
    friend class VariantPrivate;

    VariantPrivate *data;

public:
    enum Type {
        Null,
        Integer,
        Float,
        Char,
        String
    };

public:
    Variant();
    Variant(int value);
    Variant(double value);
    Variant(char value);
    Variant(string value);
    Variant(const char *value);

    Variant(const Variant &v);
    Variant &operator=(const Variant &v);

    ~Variant();

    Type type() const;

    int toInteger() const;
    double toFloat() const;
    char toChar() const;
    string toString() const;

    bool isNull() const;
};
