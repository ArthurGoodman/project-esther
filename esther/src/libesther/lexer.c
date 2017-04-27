#include "esther/lexer.h"

#include "esther/array.h"
#include "esther/esther.h"
#include "esther/id.h"
#include "esther/string.h"
#include "esther/symbol.h"
#include "esther/tuple.h"

Object *Lexer_new(Esther *es) {
    Object *self = malloc(sizeof(Lexer));
    Object_init(es, self, TObject, es->objectClass);
    return self;
}

static char sym(Lexer *lexer) {
    return lexer->pos < lexer->length ? lexer->code[lexer->pos] : '\0';
}

static char next_sym(Lexer *lexer) {
    return lexer->pos + 1 < lexer->length ? lexer->code[lexer->pos + 1] : '\0';
}

static char read_sym(Lexer *lexer) {
    char c = sym(lexer);
    lexer->pos++;
    return c;
}

static Object *scan(Esther *es, Lexer *lexer) {
    Object *token = Tuple_new_init_null(es, 2);

    Object *id;
    Object *text = String_new(es, "");

    while (isspace(sym(lexer)))
        lexer->pos++;

    if (sym(lexer) == '\0')
        id = Symbol_new(es, "");
    else if (isdigit(sym(lexer))) {
        id = Symbol_new(es, "#");

        while (isdigit(sym(lexer)))
            String_append_char(text, read_sym(lexer));

        if (sym(lexer) == '.' && isdigit(next_sym(lexer))) {
            do
                String_append_char(text, read_sym(lexer));
            while (isdigit(sym(lexer)));
        }
    } else if (isalpha(sym(lexer))) {
        id = Symbol_new(es, "id");

        while (isalnum(sym(lexer)))
            String_append_char(text, read_sym(lexer));
    } else {
        id = Symbol_new(es, "?");
        String_append_char(text, read_sym(lexer));
    }

    Tuple_set(token, 0, id);
    Tuple_set(token, 1, text);

    return token;
}

Object *Lexer_lex(Esther *es, Object *self, Object *code) {
    Lexer *lexer = (Lexer *)self;

    lexer->code = String_c_str(code);
    lexer->length = strlen(lexer->code);
    lexer->pos = 0;
    lexer->tokens = Array_new(es, 0);

    Object *token;

    do
        Array_push(lexer->tokens, token = scan(es, lexer));
    while (Symbol_getId(Tuple_get(token, 0)) != id_empty);

    return lexer->tokens;
}
