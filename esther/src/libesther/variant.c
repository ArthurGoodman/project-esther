#include "esther/variant.h"

#include <math.h>

#include "esther/common.h"
#include "esther/std_string.h"

Variant Variant_null() {
    Variant var;
    var.type = NullVariant;
    return var;
}

Variant Variant_char(char value) {
    Variant var;
    var.type = CharVariant;
    var.character = value;
    return var;
}

Variant Variant_int(int64_t value) {
    Variant var;
    var.type = IntVariant;
    var.integer = value;
    return var;
}

Variant Variant_real(double value) {
    Variant var;
    var.type = RealVariant;
    var.real = value;
    return var;
}

VariantType Variant_getType(Variant var) {
    return var.type;
}

bool Variant_isNull(Variant var) {
    return var.type == NullVariant;
}

Variant Variant_convertTo(Variant var, VariantType type) {
    switch (type) {
    case CharVariant:
        return Variant_char(Variant_toChar(var));

    case IntVariant:
        return Variant_int(Variant_toInt(var));

    case RealVariant:
        return Variant_real(Variant_toReal(var));

    default:
        return Variant_null();
    }
}

char Variant_toChar(Variant var) {
    switch (var.type) {
    case CharVariant:
        return var.character;

    case IntVariant:
        return var.integer;

    case RealVariant:
        return var.real;

    default:
        return 0;
    }
}

int64_t Variant_toInt(Variant var) {
    switch (var.type) {
    case CharVariant:
        return var.character;

    case IntVariant:
        return var.integer;

    case RealVariant:
        return var.real;

    default:
        return 0;
    }
}

double Variant_toReal(Variant var) {
    switch (var.type) {
    case CharVariant:
        return var.character;

    case IntVariant:
        return var.integer;

    case RealVariant:
        return var.real;

    default:
        return 0;
    }
}

Variant Variant_add(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_char(Variant_toChar(a) + Variant_toChar(b));

    case IntVariant:
        return Variant_int(Variant_toInt(a) + Variant_toInt(b));

    case RealVariant:
        return Variant_real(Variant_toReal(a) + Variant_toReal(b));

    default:
        return Variant_null();
    }
}

Variant Variant_sub(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_char(Variant_toChar(a) - Variant_toChar(b));

    case IntVariant:
        return Variant_int(Variant_toInt(a) - Variant_toInt(b));

    case RealVariant:
        return Variant_real(Variant_toReal(a) - Variant_toReal(b));

    default:
        return Variant_null();
    }
}

Variant Variant_mul(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_char(Variant_toChar(a) * Variant_toChar(b));

    case IntVariant:
        return Variant_int(Variant_toInt(a) * Variant_toInt(b));

    case RealVariant:
        return Variant_real(Variant_toReal(a) * Variant_toReal(b));

    default:
        return Variant_null();
    }
}

Variant Variant_div(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_char(Variant_toChar(a) / Variant_toChar(b));

    case IntVariant:
        return Variant_int(Variant_toInt(a) / Variant_toInt(b));

    case RealVariant:
        return Variant_real(Variant_toReal(a) / Variant_toReal(b));

    default:
        return Variant_null();
    }
}

Variant Variant_mod(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_char(Variant_toChar(a) % Variant_toChar(b));

    case IntVariant:
        return Variant_int(Variant_toInt(a) % Variant_toInt(b));

    case RealVariant:
        return Variant_real(fmod(Variant_toReal(a), Variant_toReal(b)));

    default:
        return Variant_null();
    }
}

Variant Variant_pow(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_char(pow(Variant_toChar(a), Variant_toChar(b)));

    case IntVariant:
        return Variant_int(pow(Variant_toInt(a), Variant_toInt(b)));

    case RealVariant:
        return Variant_real(pow(Variant_toReal(a), Variant_toReal(b)));

    default:
        return Variant_null();
    }
}

bool Variant_lt(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_toChar(a) < Variant_toChar(b);

    case IntVariant:
        return Variant_toInt(a) < Variant_toInt(b);

    case RealVariant:
        return Variant_toReal(a) < Variant_toReal(b);

    default:
        return false;
    }
}

bool Variant_gt(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_toChar(a) > Variant_toChar(b);

    case IntVariant:
        return Variant_toInt(a) > Variant_toInt(b);

    case RealVariant:
        return Variant_toReal(a) > Variant_toReal(b);

    default:
        return false;
    }
}

bool Variant_lte(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_toChar(a) <= Variant_toChar(b);

    case IntVariant:
        return Variant_toInt(a) <= Variant_toInt(b);

    case RealVariant:
        return Variant_toReal(a) <= Variant_toReal(b);

    default:
        return false;
    }
}

bool Variant_gte(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_toChar(a) >= Variant_toChar(b);

    case IntVariant:
        return Variant_toInt(a) >= Variant_toInt(b);

    case RealVariant:
        return Variant_toReal(a) >= Variant_toReal(b);

    default:
        return false;
    }
}

bool Variant_eq(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_toChar(a) == Variant_toChar(b);

    case IntVariant:
        return Variant_toInt(a) == Variant_toInt(b);

    case RealVariant:
        return Variant_toReal(a) == Variant_toReal(b);

    default:
        return false;
    }
}

bool Variant_ne(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_toChar(a) != Variant_toChar(b);

    case IntVariant:
        return Variant_toInt(a) != Variant_toInt(b);

    case RealVariant:
        return Variant_toReal(a) != Variant_toReal(b);

    default:
        return false;
    }
}

void Variant_coerce(Variant *a, Variant *b) {
    VariantType type = MAX(a->type, b->type);

    *a = Variant_convertTo(*a, type);
    *b = Variant_convertTo(*b, type);
}

struct string Variant_toString(Variant var) {
    switch (var.type) {
    case CharVariant:
        return string_format("%c", var.character);

    case IntVariant:
        return string_format("%lli", var.integer);

    case RealVariant:
        return string_format("%g", var.real);

    default:
        return string_new_empty();
    }
}

struct string Variant_inspect(Variant var) {
    switch (var.type) {
    case CharVariant: {
        struct string str = string_escape_buffer(&var.character, 1);
        string_assign(&str, string_format("'%s'", str.data));
        return str;
    }

    case IntVariant:
        return string_format("%lli", var.integer);

    case RealVariant:
        return string_format("%g", var.real);

    default:
        return string_new_empty();
    }
}
