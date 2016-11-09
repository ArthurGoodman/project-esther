#include "parser.h"

#include "common.h"
#include "expression.h"
#include "syntaxerror.h"
#include "tokens.h"
#include "variant.h"
#include "utility.h"
#include "runtime.h"
#include "context.h"

Expression *Parser::parse(Context *context, Tokens &tokens) {
    contexts.clear();
    contexts << context;

    this->tokens.swap(tokens);
    token = this->tokens.begin();

    Position p = token->getPosition();

    std::list<Expression *> nodes;

    while (!check(tEnd))
        nodes << oper();

    Expression *e = nodes.empty() ? Expression::Empty() : nodes.size() == 1 ? nodes.front() : Expression::Block(nodes);
    e->setPosition(p);

    return e;
}

void Parser::error(const std::string &msg, int delta) {
    throw new SyntaxError(msg, token->getPosition().shifted(delta));
}

void Parser::getToken() {
    ++token;
}

bool Parser::check(int id) {
    return *token == id;
}

bool Parser::accept(int id) {
    if (check(id)) {
        getToken();
        return true;
    }

    return false;
}

Context *Parser::context() {
    return contexts.back();
}

std::list<Expression *> Parser::parseBlock() {
    std::list<Expression *> nodes;

    while (!check(tRBrace) && !check(tEnd))
        nodes << oper();

    if (!accept(tRBrace))
        error("unmatched braces");

    return nodes;
}

std::list<Expression *> Parser::parseList() {
    std::list<Expression *> nodes;

    do
        nodes << logicOr();
    while (accept(tComma));

    return nodes;
}

Expression *Parser::parseIdentifier() {
    Expression *e = nullptr;

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
    Expression *e = expr();

    accept(tSemi);

    return e;
}

Expression *Parser::expr() {
    Expression *e = logicOr();

    while (true) {
        Position p = token->getPosition();

        if (accept(tAssign))
            e = Expression::LocalAssignment(e, logicOr());
        else if (accept(tPlusAssign))
            e = Expression::DirectCall(e, "+=", {logicOr()});
        else if (accept(tMinusAssign))
            e = Expression::DirectCall(e, "-=", {logicOr()});
        else if (accept(tMultiplyAssign))
            e = Expression::DirectCall(e, "*=", {logicOr()});
        else if (accept(tDivideAssign))
            e = Expression::DirectCall(e, "/=", {logicOr()});
        else if (accept(tModAssign))
            e = Expression::DirectCall(e, "%=", {logicOr()});
        else
            break;

        e->setPosition(p);
    }

    return e;
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
            e = Expression::DirectCall(e, "==", {relation()});
        else if (accept(tNe))
            e = Expression::DirectCall(e, "!=", {relation()});
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
            e = Expression::DirectCall(e, "<", {addSub()});
        else if (accept(tGt))
            e = Expression::DirectCall(e, ">", {addSub()});
        else if (accept(tLe))
            e = Expression::DirectCall(e, "<=", {addSub()});
        else if (accept(tGe))
            e = Expression::DirectCall(e, ">=", {addSub()});
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
            e = Expression::DirectCall(e, "+", {mulDiv()});
        else if (accept(tMinus))
            e = Expression::DirectCall(e, "-", {mulDiv()});
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
            e = Expression::DirectCall(e, "*", {power()});
        else if (accept(tDivide))
            e = Expression::DirectCall(e, "/", {power()});
        else if (accept(tMod))
            e = Expression::DirectCall(e, "%", {power()});
        else
            break;

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::power() {
    Expression *e = negate();

    while (true) {
        Position p = token->getPosition();

        if (accept(tPower))
            e = Expression::DirectCall(e, "**", {negate()});
        else
            break;

        e->setPosition(p);
    }

    return e;
}

Expression *Parser::negate() {
    Expression *e = nullptr;

    Position p = token->getPosition();

    if (accept(tNot))
        e = Expression::Not(dot());
    else
        e = dot();

    if (!e->getPosition().isValid())
        e->setPosition(p);

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
                std::list<Expression *> list = check(tRPar) ? std::list<Expression *>() : parseList();
                //                e = Expression::DynamicCall(e, body, list);
                e->setPosition(p);

                if (!accept(tRPar))
                    error("unmatched parentheses");
            } else {
                //                Expression *actualBody = accept(tAssign) ? Expression::Assignment(body, logicOr()) : body;
                //                e = Expression::ContextResolution(e, actualBody);
            }
        } else
            break;

        if (!e->getPosition().isValid())
            e->setPosition(p);
    }

    return e;
}

Expression *Parser::preffix() {
    Expression *e = nullptr;

    Position p = token->getPosition();

    if (accept(tPlus))
        e = Expression::DirectCall(suffix(), "+", {});
    else if (accept(tMinus))
        e = Expression::DirectCall(suffix(), "-", {});
    //    else if (accept(tDec))
    //        e = Expression::PreDecrement(suffix());
    //    else if (accept(tInc))
    //        e = Expression::PreIncrement(suffix());
    else
        e = suffix();

    if (!e->getPosition().isValid())
        e->setPosition(p);

    return e;
}

Expression *Parser::suffix() {
    Expression *e = term();

    Position p = token->getPosition();

    //    if (check(tLPar) || check(tLBracket))
    //        while (true) {
    //            Position p = token->getPosition();

    //            if (accept(tLPar)) {
    //                std::list<Expression *> list = check(tRPar) ? std::list<Expression *>() : parseList();
    //                e = Expression::DirectCall(e, "()", list);

    //                if (!accept(tRPar))
    //                    error("unmatched parentheses");
    //            } else if (accept(tLBracket)) {
    //                std::list<Expression *> list = check(tRBracket) ? std::list<Expression *>() : parseList();
    //                e = Expression::DirectCall(e, "[]", list);

    //                if (!accept(tRBracket))
    //                    error("unmatched brackets");
    //            } else
    //                break;

    //            e->setPosition(p);
    //        }
    //    else if (realAccept(tDec))
    //        e = Expression::PostDecrement(e);
    //    else if (realAccept(tInc))
    //        e = Expression::PostIncrement(e);

    if (!e->getPosition().isValid())
        e->setPosition(p);

    return e;
}

Expression *Parser::term() {
    Expression *e = nullptr;

    Position p = token->getPosition();

    if (check(tId) || check(tDollar)) {
        //        bool dynamic = false;
        //        Expression *type = 0, *name = parseIdentifier(dynamic) /*, *value = 0*/;

        //        //    if ((type = parseIdentifier())) {
        //        //        swap(type, name);
        //        //        type = Expression::Identifier(type);
        //        //    } else
        //        if (accept(tColon)) {
        //            Position p = token->getPosition();

        //            bool dynamic = false;
        //            if ((type = parseIdentifier(dynamic))) {
        //                type = Expression::Identifier(type, dynamic);
        //                type->setPosition(p);
        //            } else
        //                type = term();
        //        }

        //        if (type)
        //            e = Expression::IdentifierDefinition(type, name, 0, dynamic);
        //        else
        //            e = Expression::Identifier(name, dynamic);
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
        //        int id = token->getId();

        //        getToken();

        //        Expression *condition = expr(), *body, *elseBody = 0;

        //        Position p = token->getPosition();

        //        if (accept(tLBrace)) {
        //            body = Expression::List(parseBlock());
        //            body->setPosition(p);
        //        } else
        //            body = oper();

        //        while (check(tElse) || check(tElif)) {
        //            if (accept(tElse)) {
        //                Position p = token->getPosition();

        //                if (accept(tLBrace)) {
        //                    elseBody = Expression::List(parseBlock());
        //                    elseBody->setPosition(p);
        //                } else
        //                    elseBody = oper();

        //                break;
        //            } else if (check(tElif)) {
        //                token->setId(tIf);
        //                elseBody = term();
        //            }
        //        }

        //        e = id == tIf ? Expression::If(condition, body, elseBody) : Expression::While(condition, body, elseBody);
    }

    else if (accept(tTrue))
        e = Expression::Constant(context()->getRuntime()->getTrue());
    else if (accept(tFalse))
        e = Expression::Constant(context()->getRuntime()->getFalse());
    else if (accept(tNull))
        e = Expression::Constant(context()->getRuntime()->getNull());

    else if (accept(tSelf))
        e = Expression::Self();
    else if (accept(tHere))
        e = Expression::Here();

    else if (accept(tClass)) {
        //        Expression *name = 0, *superClass = 0, *body;

        //        if (check(tId)) {
        //            name = Expression::Literal(token->getText());
        //            name->setPosition(token->getPosition());

        //            getToken();
        //        }

        //        if (accept(tLt))
        //            superClass = term();

        //        Position p = token->getPosition();

        //        if (accept(tLBrace)) {
        //            body = Expression::List(parseBlock());
        //            body->setPosition(p);
        //        } else
        //            body = term();

        //        e = Expression::ClassDefinition(name, superClass, body);
    }

    else if (check(tFunction)) {
        //        int id = token->getId();
        //        getToken();

        //        bool dynamic = false;
        //        /*Pointer<Expression>*/ Expression *type = 0, *name = parseIdentifier(dynamic), *body;
        //        std::list<Expression *> params;
        //        bool variadic = false;

        //        //        GC_FRAME(LIST(params))

        //        //    if (name && (type = parseIdentifier())) {
        //        //        swap(type, name);
        //        //        type = Expression::Identifier(type);
        //        //    } else
        //        if (accept(tColon)) {
        //            Position p = token->getPosition();

        //            bool dynamic = false;
        //            if ((type = parseIdentifier(dynamic))) {
        //                type = Expression::Identifier(type, dynamic);
        //                type->setPosition(p);
        //            } else
        //                type = term();
        //        }

        //        if (accept(tLPar) && !accept(tRPar)) {
        //            bool expectDefaultArguments = false;

        //            do {
        //                Position paramPos = token->getPosition();

        //                if (accept(tElipsis)) {
        //                    variadic = true;
        //                    break;
        //                }

        //                if (!check(tId) && !check(tDollar))
        //                    error("identifier expected");

        //                bool dynamic = false;
        //                /*Pointer<Expression>*/ Expression *type = 0, *name = parseIdentifier(dynamic), *value = 0;

        //                Position p = token->getPosition();

        //                bool dynamicType;
        //                if ((type = parseIdentifier(dynamicType))) {
        //                    std::swap(type, name);
        //                    type = Expression::Identifier(type, dynamicType);
        //                    type->setPosition(p);
        //                } else if (accept(tColon)) {
        //                    Position p = token->getPosition();

        //                    bool dynamic = false;
        //                    if ((type = parseIdentifier(dynamic))) {
        //                        type = Expression::Identifier(type, dynamic);
        //                        type->setPosition(p);
        //                    } else
        //                        type = term();
        //                }

        //                if (accept(tAssign)) {
        //                    expectDefaultArguments = true;
        //                    value = logicOr();
        //                } else if (expectDefaultArguments)
        //                    error("default argument expected");

        //                Expression *param = Expression::ParameterDefinition(type, name, value, dynamic);
        //                param->setPosition(paramPos);

        //                params << param;
        //            } while (accept(tComma));

        //            if (!accept(tRPar))
        //                error("unmatched parenteses");
        //        }

        //        if (!type && accept(tArrow))
        //            type = term();

        //        Position p = token->getPosition();

        //        if (accept(tLBrace)) {
        //            body = Expression::List(parseBlock());
        //            body->setPosition(p);
        //        } else
        //            body = oper();

        //        switch (id) {
        //        case tFunction:
        //            e = Expression::FunctionDefinition(type, name, params, body, variadic, dynamic);
        //            break;

        //        case tMethod:
        //            e = Expression::MethodDefinition(type, name, params, body, variadic, dynamic);
        //            break;
        //        }
    }

    else if (accept(tNew)) {
        //        Position p = token->getPosition();

        //        if (accept(tLBrace)) {
        //            Expression *body = Expression::List(parseBlock());
        //            body->setPosition(p);

        //            e = Expression::ObjectLiteral(body);
        //        } else {
        //            /*Pointer<Expression>*/ Expression *body = term();

        //            std::list<Expression *> args;

        //            if (accept(tLPar)) {
        //                args = check(tRPar) ? std::list<Expression *>() : parseList();

        //                if (!accept(tRPar))
        //                    error("unmatched parentheses");
        //            }

        //            e = Expression::Call(body, "new", args);
        //        }
    }

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

    if (!e->getPosition().isValid())
        e->setPosition(p);

    return e;
}
