#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Lexer {
    Object base;

    const char *code;
    size_t length;
    size_t pos;
} Lexer;

Object *Lexer_new(Esther *es);

Object *Lexer_lex(Esther *es, Object *self, Object *code);

#ifdef __cplusplus
}
#endif
