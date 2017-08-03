#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

#define Token(id, text) (Tuple_new(es, 2, (id), (text)))
#define Token_id(t) (Tuple_get((t), 0))
#define Token_text(t) (Tuple_get((t), 1))

#define Token_setPosition(t, position) (Object_setAttribute((t), cstr_to_id("pos"), (position)))
#define Token_getPosition(t) (Object_getAttribute((t), cstr_to_id("pos")))

typedef struct Lexer {
    Object base;

    const char *code;
    size_t length;
    size_t pos, line, column;
    bool alert;
} Lexer;

Object *Lexer_new(Esther *es);

Object *Lexer_lex(Esther *es, Object *self, Object *code);

bool Lexer_isOneToken(Esther *es, Object *self, const char *code);

#ifdef __cplusplus
}
#endif
