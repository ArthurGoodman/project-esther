#pragma once

#include <string>

class VariantPrivate;

class Variant {
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
    Variant(const std::string &value);
    Variant(const char *value);

    Variant(const Variant &v);
    Variant(Variant &&v);

    Variant &operator=(const Variant &v);
    Variant &operator=(Variant &&v);

    ~Variant();

    Type type() const;

    int toInteger() const;
    double toFloat() const;
    char toChar() const;
    std::string toString() const;

    bool isNull() const;
};
