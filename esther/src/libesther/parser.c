#include "esther/parser.h"

#include "ast.h"
#include "esther/array.h"
#include "esther/esther.h"
#include "esther/exception.h"
#include "esther/id.h"
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
    Object *p = Token_getPosition(parser->token);

    while (true) {
        if (accept(es, parser, id_assign))
            e = AssignExpression(e, logicOr(es, parser));
        else if (accept(es, parser, id_plusAssign))
            e = PlusAssignExpression(e, logicOr(es, parser));
        else if (accept(es, parser, id_minusAssign))
            e = MinusAssignExpression(e, logicOr(es, parser));
        else if (accept(es, parser, id_multiplyAssign))
            e = MultiplyAssignExpression(e, logicOr(es, parser));
        else if (accept(es, parser, id_divideAssign))
            e = DivideAssignExpression(e, logicOr(es, parser));
        else if (accept(es, parser, id_modAssign))
            e = ModAssignExpression(e, logicOr(es, parser));
        else if (accept(es, parser, id_powerAssign))
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
        if (accept(es, parser, id_and))
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
        if (accept(es, parser, id_eq))
            e = EqExpression(e, relation(es, parser));
        else if (accept(es, parser, id_ne))
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
        if (accept(es, parser, id_lt))
            e = LtExpression(e, addSub(es, parser));
        else if (accept(es, parser, id_gt))
            e = GtExpression(e, addSub(es, parser));
        else if (accept(es, parser, id_le))
            e = LeExpression(e, addSub(es, parser));
        else if (accept(es, parser, id_ge))
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
        if (accept(es, parser, id_plus))
            e = PlusExpression(e, mulDiv(es, parser));
        else if (accept(es, parser, id_minus))
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
        if (accept(es, parser, id_multiply))
            e = MultiplyExpression(e, power(es, parser));
        else if (accept(es, parser, id_divide))
            e = DivideExpression(e, power(es, parser));
        else if (accept(es, parser, id_mod))
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

    if (accept(es, parser, id_not))
        e = NegateExpression(preffix(es, parser));
    else
        e = preffix(es, parser);

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *preffix(Esther *es, Parser *parser) {
    Object *e = NULL;
    Object *p = Token_getPosition(parser->token);

    if (accept(es, parser, id_plus))
        e = PlusExpression(ValueExpression(ValueObject_new_int(es, 0)), suffix(es, parser));
    else if (accept(es, parser, id_minus))
        e = MinusExpression(ValueExpression(ValueObject_new_int(es, 0)), suffix(es, parser));
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
                Exception_throw_new(es, "unmatched parentheses");

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
                Exception_throw_new(es, "unmatched brackets");

            e = CallExpression(AttributeExpression(e, String_new_c_str(es, "[]")), args);
        } else if (immediateAccept(es, parser, id_brackets)) {
            e = CallExpression(AttributeExpression(e, String_new_c_str(es, "[]")), Array_new(es, 0));
        } else if (accept(es, parser, id_dot)) {
            if (!check(es, parser, id_leftPar) && !check(es, parser, id_leftBrace) && !check(es, parser, id_empty)) {
                e = AttributeExpression(e, Tuple_get(parser->token, 1));
                getToken(parser);
            } else {
                bool expectRightPar = accept(es, parser, id_leftPar);

                e = DotExpression(e, logicOr(es, parser));

                if (expectRightPar && !accept(es, parser, id_rightPar))
                    Exception_throw_new(es, "unmatched parentheses");
            }
        } else
            break;
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

static Object *term(Esther *es, Parser *parser) {
    Object *e = NULL;
    Object *p = Token_getPosition(parser->token);

    if (check(es, parser, id_id)) {
        e = IdExpression(Tuple_get(parser->token, 1));
        getToken(parser);
    }

    else if (accept(es, parser, id_var)) {
        if (!check(es, parser, id_id))
            Exception_throw_new(es, "identifier expected");

        Object *name = Tuple_get(parser->token, 1);
        getToken(parser);

        if (accept(es, parser, id_assign))
            e = VarAssignExpression(name, logicOr(es, parser));
        else
            e = VarExpression(name);
    }

    else if (check(es, parser, id_int)) {
        e = ValueExpression(ValueObject_new_int(es, atoi(String_c_str(Tuple_get(parser->token, 1)))));
        getToken(parser);
    } else if (check(es, parser, id_float)) {
        e = ValueExpression(ValueObject_new_real(es, atof(String_c_str(Tuple_get(parser->token, 1)))));
        getToken(parser);
    } else if (check(es, parser, id_singleQuote)) {
        Object *value = Tuple_get(parser->token, 1);
        e = ValueExpression(String_size(value) == 1 ? ValueObject_new_char(es, String_c_str(value)[0]) : value);
        getToken(parser);
    } else if (check(es, parser, id_doubleQuote)) {
        e = ValueExpression(Tuple_get(parser->token, 1));
        getToken(parser);
    }

    else if (accept(es, parser, id_colon)) {
        e = SymbolExpression(Tuple_get(parser->token, 1));
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
            e = IfElseExpression(condition, body, expr(es, parser));
        else
            e = IfExpression(condition, body);
    }

    else if (accept(es, parser, id_while)) {
        Object *condition;
        Object *body;

        bool expectRightPar = accept(es, parser, id_leftPar);

        condition = expr(es, parser);

        if (expectRightPar && !accept(es, parser, id_rightPar))
            Exception_throw_new(es, "unmatched parentheses");

        body = expr(es, parser);

        e = WhileExpression(condition, body);
    }

    else if (accept(es, parser, id_true)) {
        e = TrueExpression;
    } else if (accept(es, parser, id_false)) {
        e = FalseExpression;
    } else if (accept(es, parser, id_null)) {
        e = NullExpression;

    } else if (accept(es, parser, id_self)) {
        e = SelfExpression;
    } else if (accept(es, parser, id_here)) {
        e = HereExpression;
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
            e = ClassInhExpression(name, expr(es, parser), superclass);
        } else
            e = ClassExpression(name, expr(es, parser));
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

        e = FunctionExpression(name, params, expr(es, parser));
    }

    else if (accept(es, parser, id_new)) {
        if (check(es, parser, id_braces) || check(es, parser, id_leftBrace))
            e = NewLiteralExpression(term(es, parser));
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

            e = NewExpression(check(es, parser, id_braces) || check(es, parser, id_leftBrace) ? term(es, parser) : Tuple_new(es, 0), name, args);
        }
    }

    else if (accept(es, parser, id_import)) {
        if (!check(es, parser, id_id))
            Exception_throw_new(es, "identifier expected");

        Object *name = Tuple_get(parser->token, 1);
        getToken(parser);

        e = ImportExpression(name);
    }

    //@TODO: change unary tuple syntax to Python-like
    else if (accept(es, parser, id_leftPar)) {
        Object *args = Array_new(es, 0);

        do
            Array_push(args, expr(es, parser));
        while (accept(es, parser, id_comma));

        if (!accept(es, parser, id_rightPar))
            Exception_throw_new(es, "unmatched parentheses");

        e = TupleExpression(args);
    } else if (accept(es, parser, id_pars)) {
        e = TupleExpression(Array_new(es, 0));
    }

    else if (accept(es, parser, id_leftBracket)) {
        Object *args = Array_new(es, 0);

        bool map = false, firstPass = true;

        do {
            Object *arg = expr(es, parser);

            if (!map && check(es, parser, id_doubleArrow)) {
                if (!firstPass)
                    Exception_throw_new(es, "unexpected '=>' in array literal");

                map = true;
            }

            firstPass = false;

            if (map) {
                if (!accept(es, parser, id_doubleArrow))
                    Exception_throw_new(es, "'=>' expected");

                arg = Tuple_new(es, 2, arg, expr(es, parser));
            }

            Array_push(args, arg);
        } while (accept(es, parser, id_comma));

        if (!accept(es, parser, id_rightBracket))
            Exception_throw_new(es, "unmatched brackets");

        if (map)
            e = MapExpression(args);
        else
            e = ArrayExpression(args);
    } else if (accept(es, parser, id_brackets)) {
        e = ArrayExpression(Array_new(es, 0));
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

        e = Array_size(nodes) == 0 ? Tuple_new(es, 0) : Array_size(nodes) == 1 ? Array_get(nodes, 0) : BlockExpression(nodes);
    } else if (accept(es, parser, id_braces)) {
        e = EmptyExpression;
    }

    else if (check(es, parser, id_empty)) {
        Exception_throw_new(es, "unexpected end of program");
    } else if (check(es, parser, id_unknown)) {
        Exception_throw_new(es, "unknown token %s", String_c_str(Object_inspect(es, Tuple_get(parser->token, 1))));
    } else {
        Exception_throw_new(es, "unexpected token %s", String_c_str(Object_inspect(es, Tuple_get(parser->token, 1))));
    }

    if (p && !Expression_hasPosition(e))
        Expression_setPosition(e, p);

    return e;
}

//@Cleanup: Get rid of boilerplate code in parser
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
