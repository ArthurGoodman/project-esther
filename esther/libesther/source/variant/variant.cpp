#include "variant.h"

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

Variant::Type Variant::type() const {
    return data->type();
}

int Variant::toInteger() const {
    return data->toInteger();
}

double Variant::toFloat() const {
    return data->toFloat();
}

char Variant::toChar() const {
    return data->toChar();
}

std::string Variant::toString() const {
    return data->toString();
}

bool Variant::isNull() const {
    return type() == Null;
}
