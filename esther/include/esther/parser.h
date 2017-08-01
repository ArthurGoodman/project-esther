#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Parser {
    Object base;

    int pos;
    Object *tokens;
    Object *token;
} Parser;

Object *Parser_new(Esther *es);

Object *Parser_parse(Esther *es, Object *self, Object *tokens);

#ifdef __cplusplus
}
#endif
