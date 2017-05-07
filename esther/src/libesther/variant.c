#include "esther/variant.h"

#include <math.h>

#include "esther/common.h"
#include "esther/std_string.h"

Variant Variant_create() {
    Variant var;
    var.type = NullVariant;
    return var;
}

Variant Variant_create_char(char value) {
    Variant var;
    var.type = CharVariant;
    var.character = value;
    return var;
}

Variant Variant_create_int(int value) {
    Variant var;
    var.type = IntVariant;
    var.integer = value;
    return var;
}

Variant Variant_create_real(double value) {
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
        return Variant_create_char(Variant_toChar(var));

    case IntVariant:
        return Variant_create_int(Variant_toInt(var));

    case RealVariant:
        return Variant_create_real(Variant_toReal(var));

    default:
        return Variant_create();
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

int Variant_toInt(Variant var) {
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
        return Variant_create_char(Variant_toChar(a) + Variant_toChar(b));

    case IntVariant:
        return Variant_create_int(Variant_toInt(a) + Variant_toInt(b));

    case RealVariant:
        return Variant_create_real(Variant_toReal(a) + Variant_toReal(b));

    default:
        return Variant_create();
    }
}

Variant Variant_sub(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_create_char(Variant_toChar(a) - Variant_toChar(b));

    case IntVariant:
        return Variant_create_int(Variant_toInt(a) - Variant_toInt(b));

    case RealVariant:
        return Variant_create_real(Variant_toReal(a) - Variant_toReal(b));

    default:
        return Variant_create();
    }
}

Variant Variant_mul(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_create_char(Variant_toChar(a) * Variant_toChar(b));

    case IntVariant:
        return Variant_create_int(Variant_toInt(a) * Variant_toInt(b));

    case RealVariant:
        return Variant_create_real(Variant_toReal(a) * Variant_toReal(b));

    default:
        return Variant_create();
    }
}

Variant Variant_div(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_create_char(Variant_toChar(a) / Variant_toChar(b));

    case IntVariant:
        return Variant_create_int(Variant_toInt(a) / Variant_toInt(b));

    case RealVariant:
        return Variant_create_real(Variant_toReal(a) / Variant_toReal(b));

    default:
        return Variant_create();
    }
}

Variant Variant_mod(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_create_char(Variant_toChar(a) % Variant_toChar(b));

    case IntVariant:
        return Variant_create_int(Variant_toInt(a) % Variant_toInt(b));

    case RealVariant:
        return Variant_create_real(fmod(Variant_toReal(a), Variant_toReal(b)));

    default:
        return Variant_create();
    }
}

Variant Variant_pow(Variant a, Variant b) {
    Variant_coerce(&a, &b);

    switch (a.type) {
    case CharVariant:
        return Variant_create_char(pow(Variant_toChar(a), Variant_toChar(b)));

    case IntVariant:
        return Variant_create_int(pow(Variant_toInt(a), Variant_toInt(b)));

    case RealVariant:
        return Variant_create_real(pow(Variant_toReal(a), Variant_toReal(b)));

    default:
        return Variant_create();
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

struct std_string *Variant_toString(Variant var) {
    switch (var.type) {
    case CharVariant:
        return std_string_format("%c", var.character);

    case IntVariant:
        return std_string_format("%i", var.integer);

    case RealVariant:
        return std_string_format("%g", var.real);

    default:
        return std_string_new();
    }
}

struct std_string *Variant_inspect(Variant var) {
    switch (var.type) {
    case CharVariant: {
        if (var.character == '\0')
            return std_string_new_init("'\\0'");

        char str[2];

        str[0] = var.character;
        str[1] = '\0';

        struct std_string *escaped = std_string_escape(str);
        struct std_string *result = std_string_format("'%s'", std_string_c_str(escaped));
        std_string_delete(escaped);

        return result;
    }

    case IntVariant:
        return std_string_format("%i", var.integer);

    case RealVariant:
        return std_string_format("%g", var.real);

    default:
        return std_string_new();
    }
}
