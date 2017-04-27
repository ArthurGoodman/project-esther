#include "esther/lexer.h"

#include "esther/esther.h"

Object *Lexer_new(Esther *es) {
    Object *self = malloc(sizeof(Lexer));
    Object_init(es, self, NULL);
    return self;
}

Object *Lexer_lex(Esther *es, Object *self, Object *code) {
    return es->nullObject;
}
