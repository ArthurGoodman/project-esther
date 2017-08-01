#include "esther/parser.h"

#include "esther/array.h"
#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/id.h"
#include "esther/string.h"
#include "esther/symbol.h"
#include "esther/tuple.h"
#include "esther/valueobject.h"
#include "identifiers.h"

static void Parser_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    Object_virtual_mapOnRefs(self, f);

    f(((Parser *) self)->tokens);
    f(((Parser *) self)->token);
}

#define Parser_virtual_finalize Object_virtual_finalize

OBJECT_VTABLE(Parser)

Object *Parser_new(Esther *es) {
    Parser *self = gc_alloc(sizeof(Parser));

    Object_init(es, &self->base, TObject, es->objectClass);

    self->tokens = NULL;
    self->token = NULL;

    *(void **) self = &vtable_for_Parser;

    return (Object *) self;
}

static void getToken(Parser *parser) {
    parser->token = Array_get(parser->tokens, parser->pos++);
}

static void ungetToken(Parser *parser) {
    parser->token = Array_get(parser->tokens, --parser->pos - 1);
}

static void error_invalidToken(Esther *es, Parser *parser) {
    Exception_throw_new(es, "invalid token %s", String_c_str(Object_inspect(es, parser->token)));
}

static bool immediateCheck(Esther *es, Parser *parser, ID id) {
    Object *symbol = Tuple_get(parser->token, 0);

    if (Object_getType(symbol) != TSymbol)
        error_invalidToken(es, parser);

    return Symbol_getId(symbol) == id;
}

static bool check(Esther *es, Parser *parser, ID id) {
    bool newLinesSkipped = false;

    while (immediateCheck(es, parser, id_newLine)) {
        newLinesSkipped = true;
        getToken(parser);
    }

    if (!immediateCheck(es, parser, id)) {
        if (newLinesSkipped)
            ungetToken(parser);

        return false;
    }

    return true;
}

static bool immediateAccept(Esther *es, Parser *parser, ID id) {
    if (immediateCheck(es, parser, id)) {
        getToken(parser);
        return true;
    }

    return false;
}

static bool accept(Esther *es, Parser *parser, ID id) {
    if (check(es, parser, id)) {
        getToken(parser);
        return true;
    }

    return false;
}

static Object *statement(Esther *es, Parser *parser);
static Object *expr(Esther *es, Parser *parser);
static Object *logicOr(Esther *es, Parser *parser);
static Object *logicAnd(Esther *es, Parser *parser);
static Object *equality(Esther *es, Parser *parser);
static Object *relation(Esther *es, Parser *parser);
static Object *addSub(Esther *es, Parser *parser);
static Object *mulDiv(Esther *es, Parser *parser);
static Object *power(Esther *es, Parser *parser);
static Object *negate(Esther *es, Parser *parser);
static Object *preffix(Esther *es, Parser *parser);
static Object *suffix(Esther *es, Parser *parser);
static Object *term(Esther *es, Parser *parser);

static Object *statement(Esther *es, Parser *parser) {
    Object *e = expr(es, parser);

    while (accept(es, parser, id_semi)) {
    }

    return e;
}

static Object *expr(Esther *es, Parser *parser) {
    Object *e = logicOr(es, parser);
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    while (true) {
        if (accept(es, parser, id_assign))
            e = Tuple_new(es, 3, sym_assign, e, logicOr(es, parser));
        else if (accept(es, parser, id_plusAssign))
            e = Tuple_new(es, 3, sym_plusAssign, e, logicOr(es, parser));
        else if (accept(es, parser, id_minusAssign))
            e = Tuple_new(es, 3, sym_minusAssign, e, logicOr(es, parser));
        else if (accept(es, parser, id_multiplyAssign))
            e = Tuple_new(es, 3, sym_multiplyAssign, e, logicOr(es, parser));
        else if (accept(es, parser, id_divideAssign))
            e = Tuple_new(es, 3, sym_divideAssign, e, logicOr(es, parser));
        else if (accept(es, parser, id_modAssign))
            e = Tuple_new(es, 3, sym_modAssign, e, logicOr(es, parser));
        else if (accept(es, parser, id_powerAssign))
            e = Tuple_new(es, 3, sym_powerAssign, e, logicOr(es, parser));
        break;
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *logicOr(Esther *es, Parser *parser) {
    Object *e = logicAnd(es, parser);
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    while (true) {
        if (accept(es, parser, id_or))
            e = Tuple_new(es, 3, sym_or, e, logicAnd(es, parser));
        else
            break;
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *logicAnd(Esther *es, Parser *parser) {
    Object *e = equality(es, parser);
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    while (true) {
        if (accept(es, parser, id_and))
            e = Tuple_new(es, 3, sym_and, e, equality(es, parser));
        else
            break;
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *equality(Esther *es, Parser *parser) {
    Object *e = relation(es, parser);
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    while (true) {
        if (accept(es, parser, id_eq))
            e = Tuple_new(es, 3, sym_eq, e, relation(es, parser));
        else if (accept(es, parser, id_ne))
            e = Tuple_new(es, 3, sym_ne, e, relation(es, parser));
        else
            break;
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *relation(Esther *es, Parser *parser) {
    Object *e = addSub(es, parser);
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    while (true) {
        if (accept(es, parser, id_lt))
            e = Tuple_new(es, 3, sym_lt, e, addSub(es, parser));
        else if (accept(es, parser, id_gt))
            e = Tuple_new(es, 3, sym_gt, e, addSub(es, parser));
        else if (accept(es, parser, id_ge))
            e = Tuple_new(es, 3, sym_ge, e, addSub(es, parser));
        else if (accept(es, parser, id_le))
            e = Tuple_new(es, 3, sym_le, e, addSub(es, parser));
        else
            break;
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *addSub(Esther *es, Parser *parser) {
    Object *e = mulDiv(es, parser);
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    while (true) {
        if (accept(es, parser, id_plus))
            e = Tuple_new(es, 3, sym_plus, e, mulDiv(es, parser));
        else if (accept(es, parser, id_minus))
            e = Tuple_new(es, 3, sym_minus, e, mulDiv(es, parser));
        else
            break;
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *mulDiv(Esther *es, Parser *parser) {
    Object *e = power(es, parser);
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    while (true) {
        if (accept(es, parser, id_multiply))
            e = Tuple_new(es, 3, sym_multiply, e, power(es, parser));
        else if (accept(es, parser, id_divide))
            e = Tuple_new(es, 3, sym_divide, e, power(es, parser));
        else if (accept(es, parser, id_mod))
            e = Tuple_new(es, 3, sym_mod, e, power(es, parser));
        else
            break;
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *power(Esther *es, Parser *parser) {
    Object *e = negate(es, parser);
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    while (true) {
        if (accept(es, parser, id_power))
            e = Tuple_new(es, 3, sym_power, e, negate(es, parser));
        else
            break;
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *negate(Esther *es, Parser *parser) {
    Object *e = NULL;
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    if (accept(es, parser, id_not))
        e = Tuple_new(es, 2, sym_not, preffix(es, parser));
    else
        e = preffix(es, parser);

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *preffix(Esther *es, Parser *parser) {
    Object *e = NULL;
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    if (accept(es, parser, id_plus))
        e = Tuple_new(es, 3, sym_plus, Tuple_new(es, 2, sym_sharp, ValueObject_new_int(es, 0)), suffix(es, parser));
    else if (accept(es, parser, id_minus))
        e = Tuple_new(es, 3, sym_minus, Tuple_new(es, 2, sym_sharp, ValueObject_new_int(es, 0)), suffix(es, parser));
    else
        e = suffix(es, parser);

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *suffix(Esther *es, Parser *parser) {
    Object *e = term(es, parser);
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    while (true) {
        if (immediateAccept(es, parser, id_leftPar)) {
            Object *args = Array_new(es, 0);

            if (!check(es, parser, id_rightPar))
                do
                    Array_push(args, expr(es, parser));
                while (accept(es, parser, id_comma));

            if (!accept(es, parser, id_rightPar))
                Exception_throw_new(es, "unmatched parentheses");

            e = Tuple_new(es, 3, sym_call, e, args);
        } else if (immediateAccept(es, parser, id_pars)) {
            e = Tuple_new(es, 3, sym_call, e, Array_new(es, 0));
        } else if (immediateAccept(es, parser, id_leftBracket)) {
            Object *args = Array_new(es, 0);

            if (!check(es, parser, id_rightBracket))
                do
                    Array_push(args, expr(es, parser));
                while (accept(es, parser, id_comma));

            if (!accept(es, parser, id_rightBracket))
                Exception_throw_new(es, "unmatched brackets");

            e = Tuple_new(es, 3, sym_call, Tuple_new(es, 3, sym_attr, e, String_new_c_str(es, "[]")), args);
        } else if (immediateAccept(es, parser, id_brackets)) {
            e = Tuple_new(es, 3, sym_call, Tuple_new(es, 3, sym_attr, e, String_new_c_str(es, "[]")), Array_new(es, 0));
        } else if (accept(es, parser, id_dot)) {
            if (!check(es, parser, id_leftPar) && !check(es, parser, id_leftBrace) && !check(es, parser, id_empty)) {
                e = Tuple_new(es, 3, sym_attr, e, Tuple_get(parser->token, 1));
                getToken(parser);
            } else {
                bool expectRightPar = accept(es, parser, id_leftPar);

                e = Tuple_new(es, 3, sym_dot, e, logicOr(es, parser));

                if (expectRightPar && !accept(es, parser, id_rightPar))
                    Exception_throw_new(es, "unmatched parentheses");
            }
        } else
            break;
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

static Object *term(Esther *es, Parser *parser) {
    Object *e = NULL;
    Object *p = Object_getAttribute(parser->token, string_const("pos"));

    if (check(es, parser, id_id)) {
        e = Tuple_new(es, 2, sym_id, Tuple_get(parser->token, 1));
        getToken(parser);
    }

    else if (accept(es, parser, id_var)) {
        if (!check(es, parser, id_id))
            Exception_throw_new(es, "unmatched parentheses");

        if (accept(es, parser, id_assign))
            e = Tuple_new(es, 3, sym_var, Tuple_get(parser->token, 1), logicOr(es, parser));
        else
            e = Tuple_new(es, 2, sym_var, Tuple_get(parser->token, 1));
    }

    else if (check(es, parser, id_int)) {
        e = Tuple_new(es, 2, sym_sharp, ValueObject_new_int(es, atoi(String_c_str(Tuple_get(parser->token, 1)))));
        getToken(parser);
    } else if (check(es, parser, id_float)) {
        e = Tuple_new(es, 2, sym_sharp, ValueObject_new_real(es, atof(String_c_str(Tuple_get(parser->token, 1)))));
        getToken(parser);
    } else if (check(es, parser, id_singleQuote)) {
        Object *value = Tuple_get(parser->token, 1);
        e = Tuple_new(es, 2, sym_sharp, String_size(value) == 1 ? ValueObject_new_char(es, String_c_str(value)[0]) : value);
        getToken(parser);
    } else if (check(es, parser, id_doubleQuote)) {
        e = Tuple_new(es, 2, sym_sharp, Tuple_get(parser->token, 1));
        getToken(parser);
    }

    else if (accept(es, parser, id_colon)) {
        e = Tuple_new(es, 2, sym_colon, Tuple_get(parser->token, 1));
        getToken(parser);
    }

    else if (accept(es, parser, id_if)) {
        Object *condition;
        Object *body;

        bool expectRightPar = accept(es, parser, id_leftPar);

        condition = expr(es, parser);

        if (expectRightPar && !accept(es, parser, id_rightPar))
            Exception_throw_new(es, "unmatched parentheses");

        body = expr(es, parser);

        if (accept(es, parser, id_else))
            e = Tuple_new(es, 4, sym_if, condition, body, expr(es, parser));
        else
            e = Tuple_new(es, 3, sym_if, condition, body);
    }

    else if (accept(es, parser, id_while)) {
        Object *condition;
        Object *body;

        bool expectRightPar = accept(es, parser, id_leftPar);

        condition = expr(es, parser);

        if (expectRightPar && !accept(es, parser, id_rightPar))
            Exception_throw_new(es, "unmatched parentheses");

        body = expr(es, parser);

        e = Tuple_new(es, 3, sym_while, condition, body);
    }

    else if (accept(es, parser, id_true)) {
        e = Tuple_new(es, 1, sym_true);
    } else if (accept(es, parser, id_false)) {
        e = Tuple_new(es, 1, sym_false);
    } else if (accept(es, parser, id_null)) {
        e = Tuple_new(es, 1, sym_null);

    } else if (accept(es, parser, id_self)) {
        e = Tuple_new(es, 1, sym_self);
    } else if (accept(es, parser, id_here)) {
        e = Tuple_new(es, 1, sym_here);
    }

    else if (accept(es, parser, id_class)) {
        Object *name;

        if (check(es, parser, id_id)) {
            name = Tuple_get(parser->token, 1);
            getToken(parser);
        } else
            name = String_new_c_str(es, "");

        if (accept(es, parser, id_lt)) {
            Object *superclass = expr(es, parser);
            e = Tuple_new(es, 4, sym_class, name, superclass, expr(es, parser));
        } else
            e = Tuple_new(es, 3, sym_class, name, expr(es, parser));
    }

    else if (accept(es, parser, id_function)) {
        Object *name;

        if (check(es, parser, id_id)) {
            name = Tuple_get(parser->token, 1);
            getToken(parser);
        } else
            name = String_new_c_str(es, "");

        Object *params = Array_new(es, 0);

        if (!accept(es, parser, id_pars) && accept(es, parser, id_leftPar) && !accept(es, parser, id_rightPar)) {
            do {
                if (!check(es, parser, id_id))
                    Exception_throw_new(es, "identifier expected");

                Array_push(params, Tuple_get(parser->token, 1));
                getToken(parser);
            } while (accept(es, parser, id_comma));

            if (!accept(es, parser, id_rightPar))
                Exception_throw_new(es, "unmatched parentheses");
        }

        e = Tuple_new(es, 4, sym_function, name, params, expr(es, parser));
    }

    else if (accept(es, parser, id_new)) {
        if (check(es, parser, id_braces) || check(es, parser, id_leftBrace))
            e = Tuple_new(es, 2, sym_new, term(es, parser));
        else {
            if (!check(es, parser, id_id))
                Exception_throw_new(es, "identifier expected");

            Object *name = Tuple_get(parser->token, 1);
            getToken(parser);

            Object *args = Array_new(es, 0);

            if (!accept(es, parser, id_pars) && accept(es, parser, id_leftPar)) {
                if (!check(es, parser, id_rightPar))
                    do
                        Array_push(args, expr(es, parser));
                    while (accept(es, parser, id_comma));

                if (!accept(es, parser, id_rightPar))
                    Exception_throw_new(es, "unmatched parentheses");
            }

            e = Tuple_new(es, 4, sym_new, name, args, check(es, parser, id_braces) || check(es, parser, id_leftBrace) ? term(es, parser) : Tuple_new(es, 0));
        }
    }

    else if (accept(es, parser, id_import)) {
        if (!check(es, parser, id_id))
            Exception_throw_new(es, "identifier expected");

        Object *name = Tuple_get(parser->token, 1);
        getToken(parser);

        e = Tuple_new(es, 2, sym_import, name);
    }

    //@TODO: change unary tuple syntax to Python-like
    else if (accept(es, parser, id_leftPar)) {
        Object *args = Array_new(es, 0);

        do
            Array_push(args, expr(es, parser));
        while (accept(es, parser, id_comma));

        if (!accept(es, parser, id_rightPar))
            Exception_throw_new(es, "unmatched parentheses");

        e = Tuple_new(es, 2, sym_pars, args);
    } else if (accept(es, parser, id_pars)) {
        e = Tuple_new(es, 2, sym_pars, Array_new(es, 0));
    }

    else if (accept(es, parser, id_leftBracket)) {
        Object *args = Array_new(es, 0);

        bool map = false, firstPass = true;

        do {
            Object *arg = expr(es, parser);

            if (!map && check(es, parser, id_doubleArrow)) {
                if (!firstPass)
                    Exception_throw_new(es, "unexpected => in array literal");

                map = true;
            }

            firstPass = false;

            if (map) {
                if (!accept(es, parser, id_doubleArrow))
                    Exception_throw_new(es, "double arrow expected");

                arg = Tuple_new(es, 2, arg, expr(es, parser));
            }

            Array_push(args, arg);
        } while (accept(es, parser, id_comma));

        if (!accept(es, parser, id_rightBracket))
            Exception_throw_new(es, "unmatched brackets");

        e = Tuple_new(es, 2, map ? sym_doubleArrow : sym_brackets, args);
    } else if (accept(es, parser, id_brackets)) {
        e = Tuple_new(es, 2, sym_brackets, Array_new(es, 0));
    }

    else if (accept(es, parser, id_leftBrace)) {
        Object *nodes = Array_new(es, 0);

        while (!check(es, parser, id_rightBrace) && !check(es, parser, id_empty)) {
            Object *node = statement(es, parser);

            if (Tuple_size(node) > 0) {
                ID id = Symbol_getId(Tuple_get(node, 0));

                if (id == id_braces) {
                    Object *array = Tuple_get(node, 1);

                    for (size_t i = 0; i < Array_size(array); i++)
                        Array_push(nodes, Array_get(array, i));
                } else
                    Array_push(nodes, node);
            }
        }

        if (!accept(es, parser, id_rightBrace))
            Exception_throw_new(es, "unmatched braces");

        e = Array_size(nodes) == 0 ? Tuple_new(es, 0) : Array_size(nodes) == 1 ? Array_get(nodes, 0) : Tuple_new(es, 2, sym_braces, nodes);
    } else if (accept(es, parser, id_braces)) {
        e = Tuple_new(es, 0);
    }

    else if (check(es, parser, id_empty)) {
        Exception_throw_new(es, "unexpected end of program");
    } else if (check(es, parser, id_unknown)) {
        Exception_throw_new(es, "unknown token %s", String_c_str(Object_inspect(es, Tuple_get(parser->token, 1))));
    } else {
        Exception_throw_new(es, "unexpected token %s", String_c_str(Object_inspect(es, Tuple_get(parser->token, 1))));
    }

    if (p && !Object_hasAttribute(e, string_const("pos")))
        Object_setAttribute(e, string_const("pos"), p);

    return e;
}

//@Cleanup: Get rid of boilerplate code in parser
Object *Parser_parse(Esther *es, Object *self, Object *tokens) {
    Parser *parser = (Parser *) self;

    parser->pos = 0;
    parser->tokens = tokens;

    getToken(parser);

    Object *nodes = Array_new(es, 0);

    while (!check(es, parser, id_empty)) {
        Object *node = statement(es, parser);

        if (Tuple_size(node) > 0) {
            ID id = Symbol_getId(Tuple_get(node, 0));

            if (id == id_braces) {
                Object *array = Tuple_get(node, 1);

                for (size_t i = 0; i < Array_size(array); i++)
                    Array_push(nodes, Array_get(array, i));
            } else
                Array_push(nodes, node);
        }
    }

    return Array_size(nodes) == 0 ? Tuple_new(es, 0) : Array_size(nodes) == 1 ? Array_get(nodes, 0) : Tuple_new(es, 2, sym_braces, nodes);
}
