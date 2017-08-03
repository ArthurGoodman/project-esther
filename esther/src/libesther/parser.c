#include "esther/parser.h"

#include "ast.h"
#include "esther/array.h"
#include "esther/exception.h"
#include "esther/lexer.h"
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
#define Parser_virtual_clone Object_virtual_clone_unimplemented

OBJECT_VTABLE(Parser)

Object *Parser_new(Esther *es) {
    Parser *self = gc_alloc(sizeof(Parser));

    Object_init(es, &self->base, TObject, NULL);

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

static void syntax_error(Esther *es, Object *pos, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    struct string msg = string_vformat(fmt, ap);
    va_end(ap);

    Object *exception = Exception_new(es, msg);
    Exception_setPos(exception, pos);

    Exception_throw(exception);
}

static bool immediateCheck(Esther *es, Parser *parser, ID id) {
    Object *symbol = Token_id(parser->token);

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

static bool check_pos(Esther *es, Parser *parser, ID id, Object **pos) {
    if (check(es, parser, id)) {
        *pos = Token_getPosition(parser->token);
        return true;
    }

    return false;
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

static bool accept_pos(Esther *es, Parser *parser, ID id, Object **pos) {
    if (check_pos(es, parser, id, pos)) {
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
static Object *prefix(Esther *es, Parser *parser);
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
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (accept_pos(es, parser, id_assign, &p))
            e = AssignExpression(e, logicOr(es, parser));
        else if (accept_pos(es, parser, id_plusAssign, &p))
            e = PlusAssignExpression(e, logicOr(es, parser));
        else if (accept_pos(es, parser, id_minusAssign, &p))
            e = MinusAssignExpression(e, logicOr(es, parser));
        else if (accept_pos(es, parser, id_multiplyAssign, &p))
            e = MultiplyAssignExpression(e, logicOr(es, parser));
        else if (accept_pos(es, parser, id_divideAssign, &p))
            e = DivideAssignExpression(e, logicOr(es, parser));
        else if (accept_pos(es, parser, id_modAssign, &p))
            e = ModAssignExpression(e, logicOr(es, parser));
        else if (accept_pos(es, parser, id_powerAssign, &p))
            e = PowerAssignExpression(e, logicOr(es, parser));
        break;
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *logicOr(Esther *es, Parser *parser) {
    Object *e = logicAnd(es, parser);
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (accept(es, parser, id_or))
            e = LogicOrExpression(e, logicAnd(es, parser));
        else
            break;
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *logicAnd(Esther *es, Parser *parser) {
    Object *e = equality(es, parser);
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (accept_pos(es, parser, id_and, &p))
            e = LogicAndExpression(e, equality(es, parser));
        else
            break;
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *equality(Esther *es, Parser *parser) {
    Object *e = relation(es, parser);
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (accept_pos(es, parser, id_eq, &p))
            e = EqExpression(e, relation(es, parser));
        else if (accept_pos(es, parser, id_ne, &p))
            e = NeExpression(e, relation(es, parser));
        else
            break;
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *relation(Esther *es, Parser *parser) {
    Object *e = addSub(es, parser);
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (accept_pos(es, parser, id_lt, &p))
            e = LtExpression(e, addSub(es, parser));
        else if (accept_pos(es, parser, id_gt, &p))
            e = GtExpression(e, addSub(es, parser));
        else if (accept_pos(es, parser, id_le, &p))
            e = LeExpression(e, addSub(es, parser));
        else if (accept_pos(es, parser, id_ge, &p))
            e = GeExpression(e, addSub(es, parser));
        else
            break;
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *addSub(Esther *es, Parser *parser) {
    Object *e = mulDiv(es, parser);
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (accept_pos(es, parser, id_plus, &p))
            e = PlusExpression(e, mulDiv(es, parser));
        else if (accept_pos(es, parser, id_minus, &p))
            e = MinusExpression(e, mulDiv(es, parser));
        else
            break;
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *mulDiv(Esther *es, Parser *parser) {
    Object *e = power(es, parser);
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (accept_pos(es, parser, id_multiply, &p))
            e = MultiplyExpression(e, power(es, parser));
        else if (accept_pos(es, parser, id_divide, &p))
            e = DivideExpression(e, power(es, parser));
        else if (accept_pos(es, parser, id_mod, &p))
            e = ModExpression(e, power(es, parser));
        else
            break;
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *power(Esther *es, Parser *parser) {
    Object *e = negate(es, parser);
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (accept(es, parser, id_power))
            e = PowerExpression(e, negate(es, parser));
        else
            break;
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *negate(Esther *es, Parser *parser) {
    Object *e = NULL;
    Object *p = Token_getPosition(parser->token);

    if (accept_pos(es, parser, id_not, &p))
        e = NegateExpression(prefix(es, parser));
    else
        e = prefix(es, parser);

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *prefix(Esther *es, Parser *parser) {
    Object *e = NULL;
    Object *p = Token_getPosition(parser->token);

    if (accept_pos(es, parser, id_plus, &p))
        e = PlusExpression(ValueExpression(ValueObject_new_int(es, 0)), suffix(es, parser));
    else if (accept_pos(es, parser, id_minus, &p))
        e = MinusExpression(ValueExpression(ValueObject_new_int(es, 0)), suffix(es, parser));
    else if (accept_pos(es, parser, id_dec, &p))
        e = CallExpression(AttributeExpression(suffix(es, parser), String_new_c_str(es, "--_")), Array_new(es, 0));
    else if (accept_pos(es, parser, id_inc, &p))
        e = CallExpression(AttributeExpression(suffix(es, parser), String_new_c_str(es, "++_")), Array_new(es, 0));
    else
        e = suffix(es, parser);

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *suffix(Esther *es, Parser *parser) {
    Object *e = term(es, parser);
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (immediateAccept(es, parser, id_leftPar)) {
            Object *args = Array_new(es, 0);

            if (!check(es, parser, id_rightPar))
                do
                    Array_push(args, expr(es, parser));
                while (accept(es, parser, id_comma));

            if (!accept(es, parser, id_rightPar))
                syntax_error(es, p, "unmatched parentheses");

            e = CallExpression(e, args);
        } else if (immediateAccept(es, parser, id_pars)) {
            e = CallExpression(e, Array_new(es, 0));
        } else if (immediateAccept(es, parser, id_leftBracket)) {
            Object *args = Array_new(es, 0);

            if (!check(es, parser, id_rightBracket))
                do
                    Array_push(args, expr(es, parser));
                while (accept(es, parser, id_comma));

            if (!accept(es, parser, id_rightBracket))
                syntax_error(es, p, "unmatched brackets");

            e = CallExpression(AttributeExpression(e, String_new_c_str(es, "[]")), args);
        } else if (immediateAccept(es, parser, id_brackets)) {
            e = CallExpression(AttributeExpression(e, String_new_c_str(es, "[]")), Array_new(es, 0));
        } else if (accept_pos(es, parser, id_dot, &p)) {
            if (!check(es, parser, id_leftPar) && !check(es, parser, id_leftBrace) && !check(es, parser, id_empty)) {
                immediateAccept(es, parser, id_newLine);
                e = AttributeExpression(e, Token_text(parser->token));
                getToken(parser);
            } else
                e = DotExpression(e, logicOr(es, parser));
        } else
            break;
    }

    if (accept_pos(es, parser, id_dec, &p))
        e = CallExpression(AttributeExpression(e, String_new_c_str(es, "_--")), Array_new(es, 0));
    else if (accept_pos(es, parser, id_inc, &p))
        e = CallExpression(AttributeExpression(e, String_new_c_str(es, "_++")), Array_new(es, 0));

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *term(Esther *es, Parser *parser) {
    Object *e = NULL;
    Object *p = Token_getPosition(parser->token);

    if (check_pos(es, parser, id_id, &p)) {
        e = IdExpression(Token_text(parser->token));
        getToken(parser);
    }

    else if (accept_pos(es, parser, id_var, &p)) {
        if (!check(es, parser, id_id))
            syntax_error(es, p, "identifier expected");

        Object *name = Token_text(parser->token);
        getToken(parser);

        if (accept(es, parser, id_assign))
            e = VarAssignExpression(name, logicOr(es, parser));
        else
            e = VarExpression(name);
    }

    else if (check_pos(es, parser, id_int, &p)) {
        e = ValueExpression(ValueObject_new_int(es, atoll(String_c_str(Token_text(parser->token)))));
        getToken(parser);
    } else if (check_pos(es, parser, id_float, &p)) {
        e = ValueExpression(ValueObject_new_real(es, atof(String_c_str(Token_text(parser->token)))));
        getToken(parser);
    } else if (check_pos(es, parser, id_singleQuote, &p)) {
        Object *value = Token_text(parser->token);
        e = ValueExpression(String_size(value) == 1 ? ValueObject_new_char(es, String_c_str(value)[0]) : value);
        getToken(parser);
    }
    //@TODO: Implement complex strings
    else if (check_pos(es, parser, id_doubleQuote, &p)) {
        e = ValueExpression(Token_text(parser->token));
        getToken(parser);
    }

    else if (accept_pos(es, parser, id_colon, &p)) {
        e = SymbolExpression(Token_text(parser->token));
        getToken(parser);
    }

    else if (accept_pos(es, parser, id_if, &p)) {
        Object *condition;
        Object *body;

        condition = expr(es, parser);
        body = expr(es, parser);

        if (accept(es, parser, id_else))
            e = IfElseExpression(condition, body, expr(es, parser));
        else
            e = IfExpression(condition, body);
    }

    else if (accept_pos(es, parser, id_while, &p)) {
        Object *condition;
        Object *body;

        condition = expr(es, parser);
        body = expr(es, parser);

        e = WhileExpression(condition, body);
    }

    else if (accept_pos(es, parser, id_do, &p)) {
        Object *body;
        Object *condition;

        body = expr(es, parser);

        if (!accept(es, parser, id_while))
            syntax_error(es, p, "while expected");

        condition = expr(es, parser);

        e = DoExpression(condition, body);
    }

    else if (accept_pos(es, parser, id_true, &p)) {
        e = TrueExpression;
    } else if (accept_pos(es, parser, id_false, &p)) {
        e = FalseExpression;
    } else if (accept_pos(es, parser, id_null, &p)) {
        e = NullExpression;

    } else if (accept_pos(es, parser, id_self, &p)) {
        e = SelfExpression;
    } else if (accept_pos(es, parser, id_here, &p)) {
        e = HereExpression;
    }

    else if (accept_pos(es, parser, id_class, &p)) {
        Object *name;

        if (check(es, parser, id_id)) {
            name = Token_text(parser->token);
            getToken(parser);
        } else
            name = String_new_c_str(es, "");

        if (accept(es, parser, id_lt)) {
            Object *superclass = expr(es, parser);
            e = ClassInhExpression(name, superclass, expr(es, parser));
        } else
            e = ClassExpression(name, expr(es, parser));
    }

    else if (accept_pos(es, parser, id_function, &p)) {
        Object *name;

        if (check(es, parser, id_id)) {
            name = Token_text(parser->token);
            getToken(parser);
        } else
            name = String_new_c_str(es, "");

        Object *params = Array_new(es, 0);

        if (!accept(es, parser, id_pars) && accept(es, parser, id_leftPar) && !accept(es, parser, id_rightPar)) {
            do {
                if (!check(es, parser, id_id))
                    syntax_error(es, p, "identifier expected");

                Array_push(params, Token_text(parser->token));
                getToken(parser);
            } while (accept(es, parser, id_comma));

            if (!accept(es, parser, id_rightPar))
                syntax_error(es, p, "unmatched parentheses");
        }

        e = FunctionExpression(name, params, expr(es, parser));
    }

    else if (accept_pos(es, parser, id_new, &p)) {
        if (check(es, parser, id_braces) || check(es, parser, id_leftBrace))
            e = NewLiteralExpression(term(es, parser));
        else {
            if (!check(es, parser, id_id))
                syntax_error(es, p, "identifier expected");

            Object *name = Token_text(parser->token);
            getToken(parser);

            Object *args = Array_new(es, 0);

            if (!accept(es, parser, id_pars) && accept(es, parser, id_leftPar)) {
                if (!check(es, parser, id_rightPar))
                    do
                        Array_push(args, expr(es, parser));
                    while (accept(es, parser, id_comma));

                if (!accept(es, parser, id_rightPar))
                    syntax_error(es, p, "unmatched parentheses");
            }

            e = NewExpression(name, args, check(es, parser, id_braces) || check(es, parser, id_leftBrace) ? term(es, parser) : Tuple_new(es, 0));
        }
    }

    else if (accept_pos(es, parser, id_import, &p)) {
        if (!check(es, parser, id_id))
            syntax_error(es, p, "identifier expected");

        Object *name = Token_text(parser->token);
        getToken(parser);

        e = ImportExpression(name);
    }

    else if (accept_pos(es, parser, id_leftPar, &p)) {
        Object *args = NULL;

        if (!check(es, parser, id_rightPar))
            e = expr(es, parser);
        else
            e = TupleExpression(Array_new(es, 0));

        if (accept(es, parser, id_comma)) {
            args = Array_new(es, 1, e);

            if (!check(es, parser, id_rightPar))
                do {
                    if (check(es, parser, id_rightPar))
                        break;

                    Array_push(args, expr(es, parser));
                } while (accept(es, parser, id_comma));
        }

        if (!accept(es, parser, id_rightPar))
            syntax_error(es, p, "unmatched parentheses");

        if (args)
            e = TupleExpression(args);
    } else if (accept_pos(es, parser, id_pars, &p)) {
        e = TupleExpression(Array_new(es, 0));
    }

    else if (accept_pos(es, parser, id_leftBracket, &p)) {
        Object *args = Array_new(es, 0);

        if (!check(es, parser, id_rightBracket)) {
            bool map = false, firstPass = true;

            do {
                if (check(es, parser, id_rightBracket))
                    break;

                Object *arg = expr(es, parser);

                if (!map && check(es, parser, id_doubleArrow)) {
                    if (!firstPass)
                        syntax_error(es, p, "unexpected '=>' in array literal");

                    map = true;
                }

                firstPass = false;

                if (map) {
                    if (!accept(es, parser, id_doubleArrow))
                        syntax_error(es, p, "'=>' expected");

                    arg = Tuple_new(es, 2, arg, expr(es, parser));
                }

                Array_push(args, arg);
            } while (accept(es, parser, id_comma));

            if (map)
                e = MapExpression(args);
            else
                e = ArrayExpression(args);
        } else
            e = ArrayExpression(Array_new(es, 0));

        if (!accept(es, parser, id_rightBracket))
            syntax_error(es, p, "unmatched brackets");
    } else if (accept_pos(es, parser, id_brackets, &p)) {
        e = ArrayExpression(Array_new(es, 0));
    }

    else if (accept_pos(es, parser, id_leftBrace, &p)) {
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
            syntax_error(es, p, "unmatched braces");

        e = Array_size(nodes) == 0 ? Tuple_new(es, 0) : Array_size(nodes) == 1 ? Array_get(nodes, 0) : BlockExpression(nodes);
    } else if (accept_pos(es, parser, id_braces, &p)) {
        e = EmptyExpression;
    }

    else if (check_pos(es, parser, id_empty, &p)) {
        syntax_error(es, p, "unexpected end of program");
    } else if (check_pos(es, parser, id_unknown, &p)) {
        syntax_error(es, p, "unknown token %s", String_c_str(Object_inspect(es, Token_text(parser->token))));
    } else {
        syntax_error(es, p, "unexpected token %s", String_c_str(Object_inspect(es, Token_text(parser->token))));
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

//@TODO: Implement for loop via ranges
Object *Parser_parse(Esther *es, Object *self, Object *tokens) {
    Parser *parser = (Parser *) self;

    parser->pos = 0;
    parser->tokens = tokens;

    getToken(parser);

    Object *p = Token_getPosition(parser->token);

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

    Object *e = Array_size(nodes) == 0 ? Tuple_new(es, 0) : Array_size(nodes) == 1 ? Array_get(nodes, 0) : Tuple_new(es, 2, sym_braces, nodes);

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}
