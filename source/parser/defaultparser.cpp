#include "defaultparser.h"

#include "tokens.h"
#include "syntaxerror.h"
#include "expression.h"
#include "integer.h"
#include "float.h"
#include "character.h"
#include "string.h"
#include "esther.h"
#include "utility.h"
#include "runtime.h"

Expression *DefaultParser::parse(Tokens &tokens) {
    this->tokens.swap(tokens);
    token = this->tokens.begin();

    list<Expression *> nodes;

    while (!check(tEnd))
        nodes << oper();

    return Expression::List(nodes);
}

void DefaultParser::error(string msg, int delta) {
    ErrorException *e = new SyntaxError(msg, token->getPos().shifted(delta));
    e->raise();
}

bool DefaultParser::check(int id) {
    return *token == id;
}

bool DefaultParser::accept(int id) {
    if (*token == id) {
        getToken();
        return true;
    }

    return false;
}

void DefaultParser::getToken() {
    ++token;
}

list<Expression *> DefaultParser::parseBlock() {
    list<Expression *> nodes;

    while (!check(tRBrace) && !check(tEnd))
        nodes << oper();

    if (!accept(tRBrace))
        error("unmatched braces");

    return nodes;
}

list<Expression *> DefaultParser::parseList() {
    list<Expression *> nodes;

    do
        nodes << logicOr();
    while (accept(tComma));

    return nodes;
}

Expression *DefaultParser::parseIdentifier() {
    Expression *e = 0;

    if (check(tId)) {
        e = Expression::Literal(new String(token->getText()));
        getToken();
    } else if (accept(tDollar)) {
        if (check(tLPar) || check(tLBrace) || check(tEnd))
            e = term();
        else {
            e = Expression::Literal(new String(token->getText()));
            getToken();
        }
    }

    return e;
}

Expression *DefaultParser::oper() {
    Expression *e = expr();

    accept(tSemi);

    return e;
}

Expression *DefaultParser::expr() {
    Expression *e = tuple();

    forever {
        if (accept(tAssign))
            e = Expression::Call(e, "=", tuple());
        else if (accept(tPlusAssign))
            e = Expression::Call(e, "+=", tuple());
        else if (accept(tMinusAssign))
            e = Expression::Call(e, "-=", tuple());
        else if (accept(tMultiplyAssign))
            e = Expression::Call(e, "*=", tuple());
        else if (accept(tDivideAssign))
            e = Expression::Call(e, "/=", tuple());
        else if (accept(tModAssign))
            e = Expression::Call(e, "%=", tuple());
        else
            break;
    }

    return e;
}

Expression *DefaultParser::tuple() {
    list<Expression *> nodes = parseList();

    return nodes.size() == 1 ? nodes.front() : Expression::TupleLiteral(nodes);
}

Expression *DefaultParser::logicOr() {
    Expression *e = logicAnd();

    while (accept(tOr))
        e = Expression::Or(e, logicAnd());

    return e;
}

Expression *DefaultParser::logicAnd() {
    Expression *e = equality();

    while (accept(tAnd))
        e = Expression::And(e, equality());

    return e;
}

Expression *DefaultParser::equality() {
    Expression *e = relation();

    forever {
        if (accept(tEq))
            e = Expression::Call(e, "==", relation());
        else if (accept(tNe))
            e = Expression::Call(e, "!=", relation());
        else
            break;
    }

    return e;
}

Expression *DefaultParser::relation() {
    Expression *e = addSub();

    forever {
        if (accept(tLt))
            e = Expression::Call(e, "<", addSub());
        else if (accept(tGt))
            e = Expression::Call(e, ">", addSub());
        else if (accept(tLe))
            e = Expression::Call(e, "<=", addSub());
        else if (accept(tGe))
            e = Expression::Call(e, ">=", addSub());
        else
            break;
    }

    return e;
}

Expression *DefaultParser::addSub() {
    Expression *e = mulDiv();

    forever {
        if (accept(tPlus))
            e = Expression::Call(e, "+", mulDiv());
        else if (accept(tMinus))
            e = Expression::Call(e, "-", mulDiv());
        else
            break;
    }

    return e;
}

Expression *DefaultParser::mulDiv() {
    Expression *e = dot();

    forever {
        if (accept(tMultiply))
            e = Expression::Call(e, "*", dot());
        else if (accept(tDivide))
            e = Expression::Call(e, "/", dot());
        else if (accept(tMod))
            e = Expression::Call(e, "%", dot());
        else
            break;
    }

    return e;
}

Expression *DefaultParser::dot() {
    Expression *e = preffix();

    if (accept(tDot)) {
        if (!check(tId) && !check(tColon) && !check(tLPar) && !check(tLBrace) && !check(tEnd))
            token->setId(tId);

        e = Expression::ContextResolution(e, dot());
    }

    return e;
}

Expression *DefaultParser::preffix() {
    Expression *e = 0;

    if (accept(tPlus))
        e = Expression::Call(suffix(), "+");
    else if (accept(tMinus))
        e = Expression::Call(suffix(), "-");
    else if (accept(tNot))
        e = Expression::Negate(suffix());
    else if (accept(tDec))
        e = Expression::PreDecrement(suffix());
    else if (accept(tInc))
        e = Expression::PreIncrement(suffix());
    else
        e = suffix();

    return e;
}

Expression *DefaultParser::suffix() {
    Expression *e = term();

    if (check(tLPar) || check(tLBracket))
        forever {
            if (accept(tLPar)) {
                e = Expression::Call(e, "()", check(tRPar) ? list<Expression *>() : parseList());

                if (!accept(tRPar))
                    error("unmatched parentheses");
            } else if (accept(tLBracket)) {
                e = Expression::Call(e, "[]", check(tRBracket) ? list<Expression *>() : parseList());

                if (!accept(tRBracket))
                    error("unmatched brackets");
            } else
                break;
        }
    else if (accept(tDec))
        e = Expression::PostDecrement(e);
    else if (accept(tInc))
        e = Expression::PostIncrement(e);

    return e;
}

Expression *DefaultParser::term() {
    Expression *e = 0;

    if (check(tId) || check(tDollar)) {
        Expression *type = 0, *name = parseIdentifier(), *value = 0;

        if ((type = parseIdentifier())) {
            swap(type, name);
            type = Expression::Identifier(type);
        } else if (accept(tColon)) {
            if ((type = parseIdentifier()))
                type = Expression::Identifier(type);
            else
                type = term();
        }

        if (accept(tAssign))
            value = tuple();

        if (type)
            e = Expression::IdentifierDefinition(type, name, value);
        else if (value)
            e = Expression::IdentifierAssignment(name, value);
        else
            e = Expression::Identifier(name);
    } else if (accept(tVar)) {
        Expression *name = parseIdentifier();

        if (!name) {
            name = Expression::Literal(new String(token->getText()));
            getToken();
        }

        e = Expression::IdentifierDefinition(0, name, accept(tAssign) ? logicOr() : 0);
    }

    else if (check(tInteger)) {
        e = Expression::Literal(new Integer(Utility::fromString<int>(token->getText())));
        getToken();
    } else if (check(tFloat)) {
        e = Expression::Literal(new Float(Utility::fromString<double>(token->getText())));
        getToken();
    }

    else if (check(tString)) {
        e = Expression::Literal(token->getText().size() == 1 ? (Object *)new Character(token->getText()[0]) : (Object *)new String(token->getText()));
        getToken();
    } else if (check(tComplexString)) {
        e = Expression::Literal(new String(token->getText()));
        getToken();
    }

    else if (check(tIf) || check(tWhile)) {
        int id = token->getId();

        getToken();

        Expression *condition = expr(), *body = accept(tLBrace) ? Expression::List(parseBlock()) : oper(), *elseBody = 0;

        while (check(tElse) || check(tElif)) {
            if (accept(tElse)) {
                elseBody = accept(tLBrace) ? Expression::List(parseBlock()) : oper();
                break;
            } else if (check(tElif)) {
                token->setId(tIf);
                elseBody = term();
            }
        }

        e = id == tIf ? Expression::If(condition, body, elseBody) : Expression::While(condition, body, elseBody);
    } else if (accept(tForever))
        e = Expression::While(Expression::Literal(Runtime::getTrue()), accept(tLBrace) ? Expression::List(parseBlock()) : oper(), 0);
    //else if (accept(tFor)) {
    //    if (!accept(tLPar))
    //        error("left parenthesis expected");

    //    list<Expression *> nodes = parseList();

    //    if (!accept(tRPar))
    //        error("unmatched parentheses");
    //    if (nodes.size() != 3)
    //        error("three expressions expected");

    //    list<Expression *>::iterator i = nodes.begin();
    //    Expression *preffix = *i++, *condition = *i++, *suffix = *i++;

    //    e = Expression::For(preffix, condition, suffix, oper());
    //}
    else if (accept(tDo)) {
        Expression *body = accept(tLBrace) ? Expression::List(parseBlock()) : oper();

        if (!accept(tWhile))
            error("while expected");

        e = Expression::Do(body, term());
    }

    else if (accept(tReturn))
        e = Expression::Return(check(tRPar) || check(tRBrace) || check(tEnd) || accept(tSemi) ? 0 : expr());
    else if (accept(tBreak))
        e = Expression::Break(check(tRPar) || check(tRBrace) || check(tEnd) || accept(tSemi) ? 0 : expr());
    else if (accept(tContinue))
        e = Expression::Continue();

    else if (accept(tTrue))
        e = Expression::Literal(Runtime::getTrue());
    else if (accept(tFalse))
        e = Expression::Literal(Runtime::getFalse());
    else if (accept(tNull))
        e = Expression::Literal(Runtime::getNull());

    else if (accept(tSelf))
        e = Expression::Self();
    else if (accept(tHere))
        e = Expression::Here();
    //else if (accept(tSuper))
    //e = new SuperExpression;

    else if (accept(tStatic))
        e = Expression::Static(oper());

    else if (accept(tClass)) {
        Expression *name = 0, *superClass = 0, *body;

        if (check(tId)) {
            name = Expression::Literal(new ValueObject(token->getText()));
            getToken();
        }

        if (accept(tLt))
            superClass = term();

        body = accept(tLBrace) ? Expression::List(parseBlock()) : term();

        e = Expression::ClassDefinition(name, superClass, body);
    }

    else if (check(tFunction) || check(tMethod)) {
        int id = token->getId();
        getToken();

        Expression *type = 0, *name = parseIdentifier(), *body;
        list<Expression *> params;
        bool variadic = false;

        if (name && (type = parseIdentifier())) {
            swap(type, name);
            type = Expression::Identifier(type);
        } else if (accept(tColon)) {
            if ((type = parseIdentifier()))
                type = Expression::Identifier(type);
            else
                type = term();
        }

        if (accept(tLPar) && !accept(tRPar)) {
            bool expectDefaultArguments = false;

            do {
                if (accept(tElipsis)) {
                    variadic = true;
                    break;
                }

                if (!check(tId) && !check(tDollar))
                    error("identifier expected");

                Expression *type = 0, *name = parseIdentifier(), *value = 0;

                if ((type = parseIdentifier())) {
                    swap(type, name);
                    type = Expression::Identifier(type);
                } else if (accept(tColon)) {
                    if ((type = parseIdentifier()))
                        type = Expression::Identifier(type);
                    else
                        type = term();
                }

                if (accept(tAssign)) {
                    expectDefaultArguments = true;
                    value = logicOr();
                } else if (expectDefaultArguments)
                    error("default argument expected");

                params << Expression::ParameterDefinition(type, name, value);
            } while (accept(tComma));

            if (!accept(tRPar))
                error("unmatched parenteses");
        }

        if (!type && accept(tArrow))
            type = term();

        body = accept(tLBrace) ? Expression::List(parseBlock()) : oper();

        switch (id) {
        case tFunction:
            e = Expression::FunctionDefinition(type, name, params, body, variadic);
            break;

        case tMethod:
            e = Expression::MethodDefinition(type, name, params, body, variadic);
            break;
        }
    }

    else if (accept(tNew)) {
        Expression *body = term();

        list<Expression *> args;

        if (accept(tLPar)) {
            args = check(tRPar) ? list<Expression *>() : parseList();

            if (!accept(tRPar))
                error("unmatched parentheses");
        }

        e = Expression::Call(body, "new", args);
    }

    //else if(accept(tTry)) {}

    else if (accept(tLPar)) {
        e = expr();

        if (!accept(tRPar))
            error("unmatched parentheses");
    } else if (accept(tLBrace))
        e = Expression::Block(parseBlock());

    else if (accept(tSemi))
        e = Expression::Empty();

    else if (check(tEnd))
        error("unexpected end of program");
    else if (check(tUnknown))
        error("unknown token '" + token->getText() + "'");
    else
        error("unexpected token '" + token->getText() + "'");

    return e;
}
