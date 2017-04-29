#include "esther/lexer.h"

#include "esther/array.h"
#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/id.h"
#include "esther/string.h"
#include "esther/symbol.h"
#include "esther/tuple.h"
#include "identifiers.h"

Object *Lexer_new(Esther *es) {
    Object *self = malloc(sizeof(Lexer));
    Object_init(es, self, TObject, es->objectClass);
    return self;
}

static const char *keywords[] = {
#define X(a, b) b,
#include "keywords.def"
#undef X
    ""
};

static const char *operators[] = {
#define X(a, b) b,
#include "operators.def"
#undef X
    ""
};

static bool issign(char c) {
    return c == '-' || c == '+';
}

static char sym(Lexer *lexer) {
    return lexer->pos < lexer->length ? lexer->code[lexer->pos] : '\0';
}

static char next_sym(Lexer *lexer) {
    return lexer->pos + 1 < lexer->length ? lexer->code[lexer->pos + 1] : '\0';
}

static char after_next_sym(Lexer *lexer) {
    return lexer->pos + 2 < lexer->length ? lexer->code[lexer->pos + 2] : '\0';
}

static char read_sym(Lexer *lexer) {
    char c = sym(lexer);
    lexer->pos++;
    return c;
}

static void skip_spaces(Lexer *lexer) {
    while (isspace(sym(lexer)))
        read_sym(lexer);
}

static int find_str(const char *array[], const char *str) {
    int i = 0;

    while (true) {
        if (strcmp(array[i], "") == 0) {
            i = -1;
            break;
        }

        if (strcmp(array[i], str) == 0)
            break;

        i++;
    }

    return i;
}

static Object *scan(Esther *es, Lexer *lexer) {
    Object *id = sym_empty;
    Object *text = String_new(es, "");

    skip_spaces(lexer);

    if (sym(lexer) == '/' && next_sym(lexer) == '/')
        while (sym(lexer) == '/' && next_sym(lexer) == '/') {
            while (sym(lexer) && sym(lexer) != '\n')
                read_sym(lexer);

            skip_spaces(lexer);
        }

    if (!sym(lexer)) {
    } else if (sym(lexer) == '\'' || sym(lexer) == '"') {
        char type = read_sym(lexer);

        id = type == '\'' ? sym_singleQuote : sym_doubleQuote;

        while (sym(lexer) && sym(lexer) != type) {
            if (sym(lexer) == '\n')
                break;

            if (sym(lexer) == '\\') {
                read_sym(lexer);

                switch (sym(lexer)) {
                case 'n':
                    String_append_char(text, '\n');
                    break;
                case 't':
                    String_append_char(text, '\t');
                    break;
                case '0':
                    String_append_char(text, '\0');
                    break;
                case '\\':
                    String_append_char(text, '\\');
                    break;
                case '\'':
                    String_append_char(text, '\'');
                    break;
                case '"':
                    String_append_char(text, '"');
                    break;
                case '\n':
                    break;

                default:
                    Exception_throw(es, "invalid escape sequence '\\%c'", sym(lexer));
                }

                read_sym(lexer);
            } else
                String_append_char(text, read_sym(lexer));
        }

        if (sym(lexer) != type)
            Exception_throw(es, "invalid string constant");

        read_sym(lexer);
    } else if (isdigit(sym(lexer))) {
        id = sym_int;

        while (isdigit(sym(lexer)))
            String_append_char(text, read_sym(lexer));

        if (sym(lexer) == '.' && isdigit(next_sym(lexer))) {
            id = sym_float;

            do
                String_append_char(text, read_sym(lexer));
            while (isdigit(sym(lexer)));
        }

        if ((tolower(sym(lexer)) == 'e') && (isdigit(next_sym(lexer)) || (issign(next_sym(lexer)) && isdigit(after_next_sym(lexer))))) {
            String_append_char(text, read_sym(lexer));

            if (issign(sym(lexer)) && isdigit(next_sym(lexer)))
                do
                    String_append_char(text, read_sym(lexer));
                while (isdigit(sym(lexer)));
            else
                while (isdigit(sym(lexer)))
                    String_append_char(text, read_sym(lexer));
        }
    } else if (isalpha(sym(lexer)) || sym(lexer) == '_') {
        do
            String_append_char(text, read_sym(lexer));
        while (isalnum(sym(lexer)) || sym(lexer) == '_');

        int i = find_str(keywords, String_c_str(text));
        id = i >= 0 ? keyword_symbols[i] : sym_id;
    } else {
        int i = 0;

        while (strcmp(operators[i], "") != 0)
            for (i = 0; strcmp(operators[i], "") != 0; i++) {
                size_t size = String_size(text);

                if (strncmp(operators[i], String_c_str(text), size) == 0 && operators[i][size] == sym(lexer)) {
                    String_append_char(text, read_sym(lexer));
                    break;
                }
            }

        if (String_size(text) != 0 && (i = find_str(operators, String_c_str(text))) >= 0)
            id = operator_symbols[i];
        else {
            if (String_size(text) == 0)
                String_append_char(text, read_sym(lexer));

            id = sym_unknown;
        }
    }

    return Tuple_new(es, 2, id, text);
}

Object *Lexer_lex(Esther *es, Object *self, Object *code) {
    Lexer *lexer = (Lexer *)self;

    lexer->code = String_c_str(code);
    lexer->length = strlen(lexer->code);
    lexer->pos = 0;

    Object *tokens = Array_new(es, 0);

    Object *token;

    do
        Array_push(tokens, token = scan(es, lexer));
    while (Symbol_getId(Tuple_get(token, 0)) != id_empty);

    return tokens;
}
