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

#include "utility.h"

Variant::Data::Data() {
}

Variant::Data::Data(int value)
    : integer(value) {
}

Variant::Data::Data(double value)
    : real(value) {
}

Variant::Data::Data(char value)
    : character(value) {
}

Variant::Data::Data(const std::string &value)
    : string(value) {
}

Variant::Data::Data(const char *value)
    : string(value) {
}

Variant::Data::~Data() {
}

Variant::Variant()
    : type(Null) {
}

Variant::Variant(int value)
    : type(Integer), data(value) {
}

Variant::Variant(double value)
    : type(Real), data(value) {
}

Variant::Variant(char value)
    : type(Char), data(value) {
}

Variant::Variant(const std::string &value)
    : type(String), data(value) {
}

Variant::Variant(const char *value)
    : type(String), data(value) {
}

Variant::Variant(const Variant &v)
    : type(Null) {
    *this = v;
}

Variant &Variant::operator=(const Variant &v) {
    type = v.type;
    memcpy(&data, &v.data, sizeof(Data));
    return *this;
}

Variant::Type Variant::getType() const {
    return type;
}

int Variant::toInteger() const {
    switch (type) {
    case Integer:
        return data.integer;

    case Real:
        return data.real;

    case Char:
        return data.character;

    case String:
        return Utility::fromString<int>(data.string);

    default:
        return 0;
    }
}

double Variant::toReal() const {
    switch (type) {
    case Integer:
        return data.integer;

    case Real:
        return data.real;

    case Char:
        return data.character;

    case String:
        return Utility::fromString<double>(data.string);

    default:
        return 0;
    }
}

char Variant::toChar() const {
    switch (type) {
    case Integer:
        return data.integer;

    case Real:
        return data.real;

    case Char:
        return data.character;

    case String:
        return Utility::fromString<char>(data.string);

    default:
        return 0;
    }
}

std::string Variant::toString() const {
    switch (type) {
    case Null:
        return "";

    case Integer:
        return Utility::toString(data.integer);

    case Real:
        return Utility::toString(data.real);

    case Char:
        return Utility::toString(data.character);

    case String:
        return data.string;

    default:
        return "";
    }
}

bool Variant::isNull() const {
    return type == Null;
}

#endif
