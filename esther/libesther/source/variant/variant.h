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
        Integer,
        Real,
        Char,
        String
    };

private:
    struct Data {
        Data();
        Data(int value);
        Data(double value);
        Data(char value);
        Data(const std::string &value);
        Data(const char *value);

        ~Data();

        union {
            int integer;
            double real;
            char character;
            std::string string;
        };
    };

    Type type;
    Data data;

public:
    Variant();
    Variant(int value);
    Variant(double value);
    Variant(char value);
    Variant(const std::string &value);
    Variant(const char *value);

    Variant(const Variant &v);

    Variant &operator=(const Variant &v);

    Type getType() const;

    int toInteger() const;
    double toReal() const;
    char toChar() const;
    std::string toString() const;

    bool isNull() const;
};

#endif
