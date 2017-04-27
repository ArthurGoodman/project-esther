#include "esther/parser.h"

#include "esther/esther.h"

Object *Parser_new(Esther *es) {
    Object *self = malloc(sizeof(Parser));
    Object_init(es, self, TObject, es->objectClass);
    return self;
}

Object *Parser_parse(Esther *es, Object *self, Object *tokens) {
    return es->nullObject;
}
