#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Lexer {
    Object base;
} Lexer;

#define as_Lexer(obj) ((Lexer *)(obj))

Object *Lexer_new(Esther *es);

Object *Lexer_lex(Esther *es, Object *self, Object *code);

#ifdef __cplusplus
}
#endif
