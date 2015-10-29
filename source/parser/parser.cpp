#include "parser.h"

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

Expression *Parser::parse(Tokens &tokens) {
    this->tokens.swap(tokens);
    token = this->tokens.begin();

    list<Expression *> nodes;

    Position p = token->getPosition();

    while (!check(tEnd))
        nodes << oper();

    Expression *e = Expression::List(nodes);
    e->setPosition(p);

    return e;
}

void Parser::error(string msg, int delta) {
    ErrorException *e = new SyntaxError(msg, token->getPosition().shifted(delta));
    e->raise();
}

bool Parser::check(int id) {
    return *token == id;
}

bool Parser::accept(int id) {
    if (*token == id) {
        getToken();
        return true;
    }

    return false;
}

void Parser::getToken() {
    ++token;
}

list<Expression *> Parser::parseBlock() {
    list<Expression *> nodes;

    while (!check(tRBrace) && !check(tEnd))
        nodes << oper();

    if (!accept(tRBrace))
        error("unmatched braces");

    return nodes;
}

list<Expression *> Parser::parseList() {
    list<Expression *> nodes;

    do
        nodes << logicOr();
    while (accept(tComma));

    return nodes;
}

Expression *Parser::parseIdentifier() {
    Expression *e = 0;

    if (check(tId)) {
        e = Expression::Literal(token->getText());
        e->setPosition(token->getPosition());

        getToken();
    } else if (accept(tDollar)) {
        if (check(tLPar) || check(tLBrace) || check(tEnd))
            e = term();
        else {
            e = Expression::Literal(token->getText());
            e->setPosition(token->getPosition());

            getToken();
        }
    }

    return e;
}

Expression *Parser::oper() {
    Expression *e = context();

    accept(tSemi);

    return e;
}

Expression *Parser::context() {
    Expression *e = expr();

    while (true) {
        Position p = token->getPosition();

        if (accept(tLBrace)) {
            Expression *list = Expression::List(parseBlock());
            list->setPosition(p);

            e = Expression::ContextResolution(e, list);
        } else
            break;

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::expr() {
    Expression *e = tuple();

    while (true) {
        Position p = token->getPosition();

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

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::tuple() {
    Position p = token->getPosition();

    list<Expression *> nodes = parseList();

    if (nodes.size() == 1)
        return nodes.front();
    else {
        Expression *tuple = Expression::TupleLiteral(nodes);
        tuple->setPosition(p);

        return tuple;
    }
}

Expression *Parser::logicOr() {
    Expression *e = logicAnd();

    while (true) {
        Position p = token->getPosition();

        if (accept(tOr))
            e = Expression::Or(e, logicAnd());
        else
            break;

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::logicAnd() {
    Expression *e = equality();

    while (true) {
        Position p = token->getPosition();

        if (accept(tAnd))
            e = Expression::And(e, equality());
        else
            break;

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::equality() {
    Expression *e = relation();

    while (true) {
        Position p = token->getPosition();

        if (accept(tEq))
            e = Expression::Call(e, "==", relation());
        else if (accept(tNe))
            e = Expression::Call(e, "!=", relation());
        else
            break;

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::relation() {
    Expression *e = addSub();

    while (true) {
        Position p = token->getPosition();

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

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::addSub() {
    Expression *e = mulDiv();

    while (true) {
        Position p = token->getPosition();

        if (accept(tPlus))
            e = Expression::Call(e, "+", mulDiv());
        else if (accept(tMinus))
            e = Expression::Call(e, "-", mulDiv());
        else
            break;

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::mulDiv() {
    Expression *e = power();

    while (true) {
        Position p = token->getPosition();

        if (accept(tMultiply))
            e = Expression::Call(e, "*", power());
        else if (accept(tDivide))
            e = Expression::Call(e, "/", power());
        else if (accept(tMod))
            e = Expression::Call(e, "%", power());
        else
            break;

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::power() {
    Expression *e = dot();

    while (true) {
        Position p = token->getPosition();

        if (accept(tPower))
            e = Expression::Call(e, "**", dot());
        else
            break;

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::dot() {
    Expression *e = preffix();

    while (true) {
        Position p = token->getPosition();

        if (accept(tDot)) {
            if (!check(tDollar) && !check(tLPar) && !check(tLBrace) && !check(tEnd))
                token->setId(tId);

            Expression *body = term();

            Position p = token->getPosition();

            if (accept(tLPar)) {
                e = Expression::ContextCall(e, body, check(tRPar) ? list<Expression *>() : parseList());
                e->setPosition(p);

                if (!accept(tRPar))
                    error("unmatched parentheses");
            } else
                e = Expression::ContextResolution(e, body);
        } else
            break;

        if (!e->getPosition().isValid())
            e->setPosition(p);
    }

    return e;
}

Expression *Parser::preffix() {
    Expression *e = 0;

    Position p = token->getPosition();

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

    if (!e->getPosition().isValid())
        e->setPosition(p);

    return e;
}

Expression *Parser::suffix() {
    Expression *e = term();

    Position p = token->getPosition();

    if (check(tLPar) || check(tLBracket) /* || check(tLBrace)*/)
        while (true) {
            Position p = token->getPosition();

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

            e->setPosition(p);
        }
    else if (accept(tDec))
        e = Expression::PostDecrement(e);
    else if (accept(tInc))
        e = Expression::PostIncrement(e);

    if (!e->getPosition().isValid())
        e->setPosition(p);

    return e;
}

Expression *Parser::term() {
    Expression *e = 0;

    Position p = token->getPosition();

    if (check(tId) || check(tDollar)) {
        Expression *type = 0, *name = parseIdentifier(), *value = 0;

        //    if ((type = parseIdentifier())) {
        //        swap(type, name);
        //        type = Expression::Identifier(type);
        //    } else
        if (accept(tColon)) {
            Position p = token->getPosition();

            if ((type = parseIdentifier())) {
                type = Expression::Identifier(type);
                type->setPosition(p);
            } else
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
            name = Expression::Literal(token->getText());
            name->setPosition(token->getPosition());

            getToken();
        }

        e = Expression::IdentifierDefinition(0, name, accept(tAssign) ? logicOr() : 0);
    }

    else if (check(tInteger)) {
        e = Expression::Literal(Utility::fromString<int>(token->getText()));
        getToken();
    } else if (check(tFloat)) {
        e = Expression::Literal(Utility::fromString<double>(token->getText()));
        getToken();
    }

    else if (check(tString)) {
        if (token->getText().size() == 1)
            e = Expression::Literal(token->getText()[0]);
        else
            e = Expression::Literal(token->getText());

        getToken();
    } else if (check(tComplexString)) {
        e = Expression::Literal(token->getText());
        getToken();
    }

    else if (check(tIf) || check(tWhile)) {
        int id = token->getId();

        getToken();

        Expression *condition = expr(), *body, *elseBody = 0;

        Position p = token->getPosition();

        if (accept(tLBrace)) {
            body = Expression::List(parseBlock());
            body->setPosition(p);
        } else
            body = oper();

        while (check(tElse) || check(tElif)) {
            if (accept(tElse)) {
                Position p = token->getPosition();

                if (accept(tLBrace)) {
                    elseBody = Expression::List(parseBlock());
                    elseBody->setPosition(p);
                } else
                    elseBody = oper();

                break;
            } else if (check(tElif)) {
                token->setId(tIf);
                elseBody = term();
            }
        }

        e = id == tIf ? Expression::If(condition, body, elseBody) : Expression::While(condition, body, elseBody);
    } else if (accept(tForever)) {
        Expression *body;

        Position p = token->getPosition();

        if (accept(tLBrace)) {
            body = Expression::List(parseBlock());
            body->setPosition(p);
        } else
            body = oper();

        e = Expression::While(Expression::Constant(Runtime::getTrue()), body, 0);
    }
    //else if (accept(tFor)) {
    //    if (!accept(tLPar))
    //        error("left parenthesis expected");

    //    list<Expression *> nodes = parseList();

    //    if (!accept(tRPar))
    //        error("unmatched parentheses");
    //    if (nodes.size() != 3)
    //        error("three expressions expected");

    //    auto i = nodes.begin();
    //    Expression *preffix = *i++, *condition = *i++, *suffix = *i++;

    //    e = Expression::For(preffix, condition, suffix, oper());
    //}
    else if (accept(tDo)) {
        Expression *body;

        Position p = token->getPosition();

        if (accept(tLBrace)) {
            body = Expression::List(parseBlock());
            body->setPosition(p);
        } else
            body = oper();

        if (!accept(tWhile))
            error("while expected");

        e = Expression::Do(body, term());
    }

    else if (accept(tReturn))
        e = Expression::Return(check(tRPar) || check(tRBrace) || check(tEnd) || accept(tSemi) ? 0 : context());
    else if (accept(tBreak))
        e = Expression::Break(check(tRPar) || check(tRBrace) || check(tEnd) || accept(tSemi) ? 0 : context());
    else if (accept(tContinue))
        e = Expression::Continue();

    else if (accept(tTrue))
        e = Expression::Constant(Runtime::getTrue());
    else if (accept(tFalse))
        e = Expression::Constant(Runtime::getFalse());
    else if (accept(tNull))
        e = Expression::Constant(Runtime::getNull());

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
            name = Expression::Literal(token->getText());
            name->setPosition(token->getPosition());

            getToken();
        }

        if (accept(tLt))
            superClass = term();

        Position p = token->getPosition();

        if (accept(tLBrace)) {
            body = Expression::List(parseBlock());
            body->setPosition(p);
        } else
            body = term();

        e = Expression::ClassDefinition(name, superClass, body);
    }

    else if (check(tFunction) || check(tMethod)) {
        int id = token->getId();
        getToken();

        Expression *type = 0, *name = parseIdentifier(), *body;
        list<Expression *> params;
        bool variadic = false;

        //    if (name && (type = parseIdentifier())) {
        //        swap(type, name);
        //        type = Expression::Identifier(type);
        //    } else
        if (accept(tColon)) {
            Position p = token->getPosition();

            if ((type = parseIdentifier())) {
                type = Expression::Identifier(type);
                type->setPosition(p);
            } else
                type = term();
        }

        if (accept(tLPar) && !accept(tRPar)) {
            bool expectDefaultArguments = false;

            do {
                Position paramPos = token->getPosition();

                if (accept(tElipsis)) {
                    variadic = true;
                    break;
                }

                if (!check(tId) && !check(tDollar))
                    error("identifier expected");

                Expression *type = 0, *name = parseIdentifier(), *value = 0;

                Position p = token->getPosition();

                if ((type = parseIdentifier())) {
                    swap(type, name);
                    type = Expression::Identifier(type);
                    type->setPosition(p);
                } else if (accept(tColon)) {
                    Position p = token->getPosition();

                    if ((type = parseIdentifier())) {
                        type = Expression::Identifier(type);
                        type->setPosition(p);
                    } else
                        type = term();
                }

                if (accept(tAssign)) {
                    expectDefaultArguments = true;
                    value = logicOr();
                } else if (expectDefaultArguments)
                    error("default argument expected");

                Expression *param = Expression::ParameterDefinition(type, name, value);
                param->setPosition(paramPos);

                params << param;
            } while (accept(tComma));

            if (!accept(tRPar))
                error("unmatched parenteses");
        }

        if (!type && accept(tArrow))
            type = term();

        Position p = token->getPosition();

        if (accept(tLBrace)) {
            body = Expression::List(parseBlock());
            body->setPosition(p);
        } else
            body = oper();

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
        Position p = token->getPosition();

        if (accept(tLBrace)) {
            Expression *body = Expression::List(parseBlock());
            body->setPosition(p);

            e = Expression::ObjectLiteral(body);
        } else {
            Expression *body = term();

            list<Expression *> args;

            if (accept(tLPar)) {
                args = check(tRPar) ? list<Expression *>() : parseList();

                if (!accept(tRPar))
                    error("unmatched parentheses");
            }

            e = Expression::Call(body, "new", args);
        }
    }

    else if (accept(tInclude))
        e = Expression::Include(term());

    //else if(accept(tTry)) {}

    else if (accept(tLPar)) {
        e = context();

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

    if (!e->getPosition().isValid())
        e->setPosition(p);

    return e;
}
