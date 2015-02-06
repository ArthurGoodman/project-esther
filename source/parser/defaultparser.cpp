#include "defaultparser.h"

#include "defaultlexer.h"
#include "syntaxerror.h"
#include "expression.h"
#include "valueobject.h"
#include "esther.h"
#include "utility.h"
#include "runtime.h"

namespace esther {

Expression *DefaultParser::parse(Tokens &tokens) {
    this->tokens.swap(tokens);
    token = this->tokens.begin(); // Get the list of tokens.

    list<Expression *> nodes;

    while (!check(tEnd))
        nodes << expr();

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

bool DefaultParser::range(int a, int b) {
    return (*token).getId() >= a && (*token).getId() <= b;
}

void DefaultParser::getToken() {
    ++token;
}

list<Expression *> DefaultParser::parseBlock() {
    list<Expression *> nodes;

    while (!check(tRBrace) && !check(tEnd))
        nodes << expr();

    if (!accept(tRBrace))
        error("unmatched braces");

    return nodes;
}

list<Expression *> DefaultParser::parseList() {
    list<Expression *> nodes;

    do
        nodes << assign();
    while (accept(tComma));

    return nodes;
}

Expression *DefaultParser::expr() {
    list<Expression *> nodes = parseList();

    accept(tSemi);

    return nodes.size() == 1 ? nodes.front() : Expression::List(nodes);
}

Expression *DefaultParser::assign() {
    Expression *e = logicOr();

    while (range(tAssign, tModAssign)) {
        if (accept(tAssign))
            e = Expression::Call(e, "=", logicOr());
        else if (accept(tPlusAssign))
            e = Expression::Call(e, "+=", logicOr());
        else if (accept(tMinusAssign))
            e = Expression::Call(e, "-=", logicOr());
        else if (accept(tMultiplyAssign))
            e = Expression::Call(e, "*=", logicOr());
        else if (accept(tDivideAssign))
            e = Expression::Call(e, "/=", logicOr());
        else if (accept(tModAssign))
            e = Expression::Call(e, "%=", logicOr());
    }

    return e;
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

    while (range(tEq, tNe)) {
        if (accept(tEq))
            e = Expression::Call(e, "==", relation());
        else if (accept(tNe))
            e = Expression::Call(e, "!=", relation());
    }

    return e;
}

Expression *DefaultParser::relation() {
    Expression *e = addSub();

    while (range(tLt, tGe)) {
        if (accept(tLt))
            e = Expression::Call(e, "<", addSub());
        else if (accept(tGt))
            e = Expression::Call(e, ">", addSub());
        else if (accept(tLe))
            e = Expression::Call(e, "<=", addSub());
        else if (accept(tGe))
            e = Expression::Call(e, ">=", addSub());
    }

    return e;
}

Expression *DefaultParser::addSub() {
    Expression *e = mulDiv();

    while (range(tPlus, tMinus)) {
        if (accept(tPlus))
            e = Expression::Call(e, "+", mulDiv());
        else if (accept(tMinus))
            e = Expression::Call(e, "-", mulDiv());
    }

    return e;
}

Expression *DefaultParser::mulDiv() {
    Expression *e = dot();

    while (range(tMultiply, tMod)) {
        if (accept(tMultiply))
            e = Expression::Call(e, "*", dot());
        else if (accept(tDivide))
            e = Expression::Call(e, "/", dot());
        else if (accept(tMod))
            e = Expression::Call(e, "%", dot());
    }

    return e;
}

Expression *DefaultParser::dot() {
    Expression *e = preffix();

    while (accept(tDot)) {
        if (!check(tId) && !check(tColon) && !check(tLPar) && !check(tLBrace) && !check(tEnd))
            token->setId(tId);

        Expression *body = preffix();

        //if (dynamic_cast<BlockExpression *>(body))
        //    ((BlockExpression *)body)->disableChildContext();

        e = Expression::ContextResolution(e, body);
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
    //else if (accept(tInclude))
    //    e = new IncludeExpression(suffix());
    //else if (accept(tDot)) {
    //    if (!check(tId) && !check(tColon) && !check(tLPar) && !check(tLBrace) && !check(tDot) && !check(tEnd))
    //        (*token).setId(tId);

    //    Expression *body = assign();

    //    if (dynamic_cast<BlockExpression *>(body))
    //        ((BlockExpression *)body)->disableChildContext();

    //    e = new ContextResolutionExpression(0, body);
    //}
    else if (accept(tDec))
        e = Expression::Call(suffix(), "--");
    else if (accept(tInc))
        e = Expression::Call(suffix(), "++");
    else
        e = suffix();

    return e;
}

Expression *DefaultParser::suffix() {
    Expression *e = term();

    if (range(tLPar, tLBracket))
        while (range(tLPar, tLBracket)) {
            if (accept(tLPar)) {
                list<Expression *> nodes = check(tRPar) ? list<Expression *>() : parseList();

                e = Expression::Call(e, "()", nodes);

                if (!accept(tRPar))
                    error("unmatched parentheses");
            } else if (accept(tLBracket)) {
                list<Expression *> nodes = check(tRPar) ? list<Expression *>() : parseList();

                e = Expression::Call(e, "[]", nodes);

                if (!accept(tRBracket))
                    error("unmatched brackets");
            }
        }
    else if (accept(tDec))
        e = Expression::CloneAndCall(e, "--");
    else if (accept(tInc))
        e = Expression::CloneAndCall(e, "++");

    return e;
}

Expression *DefaultParser::term() {
    Expression *e = 0;

    //if (check(tAt) || check(tId) || check(tColon)) {
    //    bool attribute = accept(tAt);

    //    if (attribute && !check(tId) && !check(tColon))
    //        error("identifier expected");

    //    Expression *name = 0, *type = 0;

    //    if (check(tId)) {
    //        name = new LiteralExpression(/*new String(token.text())*/ 0);
    //        getToken();
    //    } else {
    //        getToken();

    //        if (check(tLPar) || check(tLBrace) || check(tEnd))
    //            name = term();
    //        else {
    //            name = new LiteralExpression(/*new String(token.text())*/ 0);
    //            getToken();
    //        }
    //    }

    //    if (accept(tColon)) {
    //        if (!check(tId) && !check(tColon))
    //            error("identifier expected");

    //        if (check(tId)) {
    //            type = new LiteralExpression(/*new String(token.text())*/ 0);
    //            getToken();
    //        } else {
    //            getToken();

    //            if (check(tLPar) || check(tLBrace) || check(tEnd))
    //                type = term();
    //            else {
    //                type = new LiteralExpression(/*new String(token.text())*/ 0);
    //                getToken();
    //            }
    //        }
    //    }

    //    e = new IdentifierExpression(name, type, accept(tAssign) ? logicOr() : 0, attribute);
    //}

    if (check(tId)) {
        Expression *name = 0, *value = 0;

        name = Expression::Literal(new ValueObject(token->getText()));
        getToken();

        if (accept(tAssign))
            value = logicOr();

        if (value)
            e = Expression::IdentifierAssignment(name, value);
        else
            e = Expression::Identifier(name);
    } else if (accept(tVar)) {
        if (!check(tId))
            error("identifier expected");

        Expression *name = Expression::Literal(new ValueObject(token->getText()));
        getToken();

        e = Expression::IdentifierDefinition(name, accept(tAssign) ? logicOr() : 0);
    }

    else if (check(tInteger)) {
        e = Expression::Literal(new ValueObject(Utility::fromString<int>(token->getText())));
        getToken();
    } else if (check(tFloat)) {
        e = Expression::Literal(new ValueObject(Utility::fromString<double>(token->getText())));
        getToken();
    }

    else if (check(tString)) {
        e = Expression::Literal(token->getText().size() == 1 ? new ValueObject(token->getText()[0]) : new ValueObject(token->getText()));
        getToken();
    } else if (check(tComplexString)) {
        e = Expression::Literal(new ValueObject(token->getText()));
        getToken();
    }

    //else if (accept(tLBracket)) {
    //    e = new ListExpression(((BlockExpression *)expr())->getExpressions());
    //    if (!accept(tRBracket))
    //        error("unmatched brackets");
    //} else if (accept(tLt)) {
    //    e = new VectorExpression(((BlockExpression *)expr())->getExpressions());
    //    if (!accept(tGt))
    //        error("unmatched brackets");
    //}

    else if (check(tIf) || check(tWhile)) {
        int id = token->getId();

        getToken();

        Expression *condition = term(), *body = expr(), *elseBody = 0;

        if (accept(tElse))
            elseBody = expr();
        else if (check(tElif)) {
            token->setId(tIf);
            elseBody = term();
        }

        e = id == tIf ? Expression::If(condition, body, elseBody) : Expression::While(condition, body, elseBody);
    } else if (accept(tForever))
        e = Expression::While(Expression::Literal(Runtime::getTrue()), expr(), 0);
    else if (accept(tFor)) {
        if (!accept(tLPar))
            error("left parenthesis expected");

        list<Expression *> nodes = parseList();

        if (!accept(tRPar))
            error("unmatched parentheses");
        if (nodes.size() != 3)
            error("three expressions expected");

        list<Expression *>::iterator i = nodes.begin();
        Expression *preffix = *i++, *condition = *i++, *suffix = *i++;

        e = Expression::For(preffix, condition, suffix, expr());
    } else if (accept(tDo)) {
        Expression *body = expr();
        if (!accept(tWhile))
            error("while expected");
        e = Expression::Do(body, term());
    }

    else if (accept(tReturn))
        e = Expression::Return(check(tRPar) || check(tRBrace) || check(tEnd) || accept(tSemi) ? 0 : assign());
    else if (accept(tBreak))
        e = Expression::Break(check(tRPar) || check(tRBrace) || check(tEnd) || accept(tSemi) ? 0 : assign());
    else if (accept(tContinue))
        e = Expression::Continue();

    else if (accept(tTrue))
        e = Expression::Literal(Runtime::getTrue());
    else if (accept(tFalse))
        e = Expression::Literal(Runtime::getFalse());
    else if (accept(tNull))
        e = Expression::Literal(Runtime::getNull());

    //else if (accept(tSelf))
    //    e = new SelfExpression;
    //else if (accept(tSuper))
    //    e = new SuperExpression;
    //else if (accept(tContext))
    //    e = new ContextExpression;

    //else if (range(tStatic, tLambda) || check(tDollar)) {
    //    bool isStatic = false;
    //    if (accept(tStatic))
    //        isStatic = true;
    //    if (!range(tMethod, tLambda) && !check(tDollar))
    //        error("method expected");

    //    int type = (*token).id();
    //    getToken();

    //    IdentifierExpression *name = 0;
    //    list<IdentifierExpression *> params;

    //    if (type == tMethod || type == tFunction || (type == tDollar && (check(tId) || check(tColon)))) {
    //        if (!check(tId) && !check(tColon))
    //            error("identifier expected");
    //        name = (IdentifierExpression *)term();
    //    }

    //    if (accept((tLPar))) {
    //        list<Expression *> expressions = check(tRPar) ? list<Expression *>() : ((BlockExpression *)expr())->getExpressions();

    //        foreach (n, expressions) {
    //            if (!dynamic_cast<IdentifierExpression *>(*n))
    //                error("identifier expected");
    //            params << *n;
    //        }

    //        if (!accept(tRPar))
    //            error("unmatched parentheses");
    //    }

    //    switch (type) {
    //    case tMethod:
    //        e = new CallableExpression(name, params, assign(), tMethod, isStatic);
    //        break;
    //    case tFunction:
    //        e = new CallableExpression(name, params, assign(), tFunction, isStatic);
    //        break;
    //    case tLambda:
    //        e = new CallableExpression(new IdentifierExpression(new LiteralExpression(/*new String("")*/ 0), 0, 0, false), params, assign(), tLambda, isStatic);
    //        break;
    //    case tDollar:
    //        e = !name ? (Expression *)new CallableExpression(new IdentifierExpression(new LiteralExpression(/*new String("")*/ 0), 0, 0, false), params, assign(), tDollar, isStatic) : (Expression *)new CallableExpression(name, params, assign(), tDollar, isStatic);
    //        break;
    //    }
    //}
    else if (accept(tClass)) {
        Expression *name = 0, *superClass = 0, *body;

        if (check(tId)) {
            name = Expression::Literal(new ValueObject(token->getText()));
            getToken();
        }

        if (accept(tLt))
            superClass = term();

        body = term();

        //if (dynamic_cast<BlockExpression *>(body))
        //    ((BlockExpression *)body)->disableChildContext();

        e = Expression::ClassDefinition(name, superClass, body);
    }

    //else if(accept(tTry)) {}

    else if (accept(tLPar)) {
        if (accept(tRPar))
            e = Expression::List();
        else {
            e = Expression::List(parseList());

            if (!accept(tRPar))
                error("unmatched parentheses");
        }
    } else if (accept(tLBrace))
        e = Expression::Block(parseBlock());

    else if (accept(tSemi))
        e = Expression::Empty();

    else if (check(tEnd))
        error("unexpected end of expression");
    else if (check(tUnknown))
        error("unknown token '" + token->getText() + "'");
    else
        error("unexpected token '" + token->getText() + "'");

    return e;
}
}
