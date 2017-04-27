#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

typedef struct Parser {
    Object base;
} Parser;

#define as_Parser(obj) ((Parser *)(obj))

Object *Parser_new(Esther *es);

Object *Parser_parse(Esther *es, Object *self, Object *tokens);

#ifdef __cplusplus
}
#endif
