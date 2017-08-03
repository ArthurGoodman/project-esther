#include "esther/lexer.h"

#include "esther/array.h"
#include "esther/exception.h"
#include "esther/string.h"
#include "esther/symbol.h"
#include "esther/tuple.h"
#include "esther/valueobject.h"
#include "identifiers.h"

Object *Lexer_new(Esther *es) {
    Object *self = gc_alloc(sizeof(Lexer));
    Object_init(es, self, TObject, NULL);
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

    if (c == '\n') {
        lexer->line++;
        lexer->column = 0;
    } else
        lexer->column++;

    lexer->pos++;

    return c;
}

static void skip_spaces(Lexer *lexer) {
    while (isspace(sym(lexer)) && sym(lexer) != '\n')
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
    Object *text = String_new_cstr(es, "");

    skip_spaces(lexer);

    size_t pos = lexer->pos;
    size_t line = lexer->line + 1;
    size_t column = lexer->column + 1;

    if (sym(lexer) == '/' && next_sym(lexer) == '/')
        while (sym(lexer) == '/' && next_sym(lexer) == '/') {
            while (sym(lexer) && sym(lexer) != '\n')
                read_sym(lexer);

            skip_spaces(lexer);
        }

    if (!sym(lexer)) {
    } else if (sym(lexer) == '\n') {
        while (isspace(sym(lexer)))
            read_sym(lexer);

        id = sym_newLine;
        text = String_new_cstr(es, "\n");
    } else if (sym(lexer) == '\'' || sym(lexer) == '"') {
        char type = read_sym(lexer);

        id = type == '\'' ? sym_singleQuote : sym_doubleQuote;

        while (sym(lexer) && sym(lexer) != type) {
            if (sym(lexer) == '\n')
                break;

            if (sym(lexer) == '\\') {
                read_sym(lexer);

                switch (sym(lexer)) {
                case '\'':
                    String_append_char(text, '\'');
                    break;
                case '"':
                    String_append_char(text, '"');
                    break;
                case '\\':
                    String_append_char(text, '\\');
                    break;
                case 'a':
                    String_append_char(text, '\a');
                    break;
                case 'b':
                    String_append_char(text, '\b');
                    break;
                case 'f':
                    String_append_char(text, '\f');
                    break;
                case 'n':
                    String_append_char(text, '\n');
                    break;
                case 'r':
                    String_append_char(text, '\r');
                    break;
                case 't':
                    String_append_char(text, '\t');
                    break;
                case 'v':
                    String_append_char(text, '\v');
                    break;
                case '0':
                    String_append_char(text, '\0');
                    break;
                case '\n':
                    break;

                default:
                    if (lexer->alert)
                        Exception_throw_new(es, "invalid escape sequence '\\%c'", sym(lexer));

                    return NULL;
                }

                read_sym(lexer);
            } else
                String_append_char(text, read_sym(lexer));
        }

        if (sym(lexer) != type) {
            if (lexer->alert)
                Exception_throw_new(es, "invalid string constant");

            return NULL;
        }

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

        int i = find_str(keywords, String_cstr(text));
        id = i >= 0 ? keyword_symbols[i] : sym_id;
    } else {
        int i = 0;

        while (strcmp(operators[i], "") != 0)
            for (i = 0; strcmp(operators[i], "") != 0; i++) {
                size_t size = String_size(text);

                if (sym(lexer) && strncmp(operators[i], String_cstr(text), size) == 0 && operators[i][size] == sym(lexer)) {
                    String_append_char(text, read_sym(lexer));
                    break;
                }
            }

        if (String_size(text) != 0 && (i = find_str(operators, String_cstr(text))) >= 0)
            id = operator_symbols[i];
        else {
            if (String_size(text) == 0)
                String_append_char(text, read_sym(lexer));

            id = sym_unknown;
        }
    }

    Object *token = Token(id, text);
    Object *position = Tuple_new(es, 3, ValueObject_new_int(es, pos), ValueObject_new_int(es, line), ValueObject_new_int(es, column));

    Token_setPosition(token, position);

    return token;
}

Object *Lexer_lex(Esther *es, Object *self, Object *code) {
    Lexer *lexer = (Lexer *) self;

    lexer->code = String_cstr(code);
    lexer->length = strlen(lexer->code);
    lexer->pos = 0;
    lexer->line = 0;
    lexer->column = 0;
    lexer->alert = true;

    Object *tokens = Array_new(es, 0);

    Object *token;

    do
        Array_push(tokens, token = scan(es, lexer));
    while (Symbol_getId(Tuple_get(token, 0)) != id_empty);

    return tokens;
}

bool Lexer_isOneToken(Esther *es, Object *self, const char *code) {
    Lexer *lexer = (Lexer *) self;

    lexer->code = code;
    lexer->length = strlen(lexer->code);
    lexer->pos = 0;
    lexer->line = 0;
    lexer->column = 0;
    lexer->alert = false;

    return !isspace(code[0]) && scan(es, lexer) && !sym(lexer);
}
