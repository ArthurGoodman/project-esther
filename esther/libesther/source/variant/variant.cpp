#include "variant.h"

#if HEAP_VARIANT

#include "nullvariant.h"
#include "integervariant.h"
#include "floatvariant.h"
#include "stringvariant.h"
#include "charvariant.h"

Variant::Variant()
    : data(new NullVariant) {
}

Variant::Variant(int value)
    : data(new IntegerVariant(value)) {
}

Variant::Variant(double value)
    : data(new FloatVariant(value)) {
}

Variant::Variant(char value)
    : data(new CharVariant(value)) {
}

Variant::Variant(const std::string &value)
    : data(new StringVariant(value)) {
}

Variant::Variant(const char *value)
    : data(new StringVariant(value)) {
}

Variant::Variant(const Variant &v)
    : data(0) {
    *this = v;
}

Variant::Variant(Variant &&v)
    : data(0) {
    *this = std::move(v);
}

Variant &Variant::operator=(const Variant &v) {
    delete data;
    data = v.data->clone();
    return *this;
}

Variant &Variant::operator=(Variant &&v) {
    delete data;
    data = v.data;
    v.data = 0;
    return *this;
}

Variant::~Variant() {
    delete data;
}

Variant::Type Variant::getType() const {
    return data->type();
}

int Variant::toInteger() const {
    return data->toInteger();
}

double Variant::toReal() const {
    return data->toReal();
}

char Variant::toChar() const {
    return data->toChar();
}

std::string Variant::toString() const {
    return data->toString();
}

bool Variant::isNull() const {
    return getType() == Null;
}

#else

#include <cstring>

#include "utility.h"

Variant::Variant()
    : type(Null) {
}

Variant::Variant(int value)
    : type(Integer), integer(value) {
}

Variant::Variant(double value)
    : type(Real), real(value) {
}

Variant::Variant(char value)
    : type(Char), character(value) {
}

Variant::Variant(const std::string &value)
    : type(String) {
    string = (char *)malloc(value.size() + 1);
    memcpy(string, value.data(), value.size() + 1);
}

Variant::Variant(const char *value)
    : type(String) {
    int size = strlen(value) + 1;
    string = (char *)malloc(size);
    memcpy(string, value, size);
}

Variant::Variant(const Variant &v)
    : type(Null) {
    *this = v;
}

Variant::Variant(Variant &&v)
    : type(Null) {
    *this = std::move(v);
}

Variant &Variant::operator=(const Variant &v) {
    if (type == String) {
        if (v.type == String) {
            int size = strlen(v.string) + 1;
            string = (char *)realloc(string, size);
            memcpy(string, v.string, size);

            return *this;
        }

        free(string);
    }

    type = v.type;

    switch (v.type) {
    case Integer:
        integer = v.integer;
        break;

    case Real:
        real = v.real;
        break;

    case Char:
        character = v.character;
        break;

    case String: {
        int size = strlen(v.string) + 1;
        string = (char *)malloc(size);
        memcpy(string, v.string, size);
        break;
    }

    default:
        break;
    }

    return *this;
}

Variant &Variant::operator=(Variant &&v) {
    if (type == String)
        free(string);

    type = v.type;

    switch (v.type) {
    case Integer:
        integer = v.integer;
        break;

    case Real:
        real = v.real;
        break;

    case Char:
        character = v.character;
        break;

    case String:
        string = v.string;
        v.string = nullptr;
        break;

    default:
        break;
    }

    return *this;
}

Variant::Type Variant::getType() const {
    return type;
}

int Variant::toInteger() const {
    switch (type) {
    case Integer:
        return integer;

    case Real:
        return real;

    case Char:
        return character;

    case String:
        return Utility::fromString<int>(string);

    default:
        return 0;
    }
}

double Variant::toReal() const {
    switch (type) {
    case Integer:
        return integer;

    case Real:
        return real;

    case Char:
        return character;

    case String:
        return Utility::fromString<double>(string);

    default:
        return 0;
    }
}

char Variant::toChar() const {
    switch (type) {
    case Integer:
        return integer;

    case Real:
        return real;

    case Char:
        return character;

    case String:
        return Utility::fromString<char>(string);

    default:
        return 0;
    }
}

std::string Variant::toString() const {
    switch (type) {
    case Integer:
        return Utility::toString(integer);

    case Real:
        return Utility::toString(real);

    case Char:
        return Utility::toString(character);

    case String:
        return string;

    default:
        return "";
    }
}

bool Variant::isNull() const {
    return type == Null;
}

#endif
