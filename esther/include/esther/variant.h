#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

struct std_string;

typedef enum VariantType {
    NullVariant,
    CharVariant,
    IntVariant,
    RealVariant
} VariantType;

typedef struct Variant {
    VariantType type;

    union {
        char character;
        int integer;
        double real;
    };
} Variant;

Variant Variant_null();
Variant Variant_char(char value);
Variant Variant_int(int value);
Variant Variant_real(double value);

VariantType Variant_getType(Variant var);

bool Variant_isNull(Variant var);

Variant Variant_convertTo(Variant var, VariantType type);

char Variant_toChar(Variant var);
int Variant_toInt(Variant var);
double Variant_toReal(Variant var);

Variant Variant_add(Variant a, Variant b);
Variant Variant_sub(Variant a, Variant b);
Variant Variant_mul(Variant a, Variant b);
Variant Variant_div(Variant a, Variant b);
Variant Variant_mod(Variant a, Variant b);
Variant Variant_pow(Variant a, Variant b);

bool Variant_lt(Variant a, Variant b);
bool Variant_gt(Variant a, Variant b);
bool Variant_lte(Variant a, Variant b);
bool Variant_gte(Variant a, Variant b);
bool Variant_eq(Variant a, Variant b);
bool Variant_ne(Variant a, Variant b);

void Variant_coerce(Variant *a, Variant *b);

struct string Variant_toString(Variant var);
struct string Variant_inspect(Variant var);

#ifdef __cplusplus
}
#endif
