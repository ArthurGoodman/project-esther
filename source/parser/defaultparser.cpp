#include "defaultparser.h"

#include "defaultlexer.h"
#include "syntaxerror.h"
#include "expression.h"
#include "valueobject.h"

namespace esther {

Expression *DefaultParser::parse(Tokens &tokens) {
    this->tokens.swap(tokens);
    token = this->tokens.begin(); // Get the list of tokens.

    list<Expression *> nodes;

    while (!check(tEnd))
        nodes << expr();

    return Expression::Block(nodes);
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

Expression *DefaultParser::expr() {
    list<Expression *> nodes;

    do
        nodes << assign();
    while (accept(tComma));

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

    accept(tSemi);

    return e;
}

Expression *DefaultParser::logicOr() {
    Expression *e = logicAnd();

    //while (accept(tOr))
    //    e = new OrExpression(e, logicXor());

    return e;
}

Expression *DefaultParser::logicAnd() {
    Expression *e = equality();

    //while (accept(tAnd))
    //    e = new AndExpression(e, equality());

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

    //while (accept(tDot)) {
    //    if (!check(tId) && !check(tColon) && !check(tLPar) && !check(tLBrace) && !check(tEnd))
    //        (*token).setId(tId);
    //    Expression *body = preffix();
    //    if (dynamic_cast<BlockExpression *>(body))
    //        ((BlockExpression *)body)->disableChildContext();
    //    e = new ContextResolutionExpression(e, body);
    //}

    return e;
}

Expression *DefaultParser::preffix() {
    Expression *e = 0;

    if (accept(tPlus))
        e = Expression::Call(Expression::Literal(/*new Integer(0)*/ 0), "+", suffix());
    else if (accept(tMinus))
        e = Expression::Call(Expression::Literal(/*new Integer(0)*/ 0), "-", suffix());
    //else if (accept(tNot))
    //    e = new NotExpression(suffix());
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
        e = Expression::Call(suffix(), "dec_", list<Expression *>());
    else if (accept(tInc))
        e = Expression::Call(suffix(), "inc_", list<Expression *>());
    else
        e = suffix();

    return e;
}

Expression *DefaultParser::suffix() {
    Expression *e = arrow();

    //if (range(tLPar, tLBracket))
    //    while (range(tLPar, tLBracket)) {
    //        if (accept(tLPar)) {
    //            list<Expression *> expressions = check(tRPar) ? list<Expression *>() : ((BlockExpression *)expr())->getExpressions();
    //            e = Expression::Call(e, "()", expressions);
    //            if (!accept(tRPar))
    //                error("unmatched parentheses");
    //        } else if (accept(tLBracket)) {
    //            e = Expression::Call(e, "[]", expr());
    //            if (!accept(tRBracket))
    //                error("unmatched brackets");
    //        }
    //    }
    //else
    if (accept(tDec))
        e = Expression::Call(e, "_dec", list<Expression *>());
    else if (accept(tInc))
        e = Expression::Call(e, "_inc", list<Expression *>());

    return e;
}

Expression *DefaultParser::arrow() {
    Expression *e = term();

    //while (accept(tArrow)) {
    //    if (!check(tId) && !check(tColon) && !check(tLPar) && !check(tLBrace) && !check(tEnd))
    //        (*token).setId(tId);

    //    IdentifierExpression *id = dynamic_cast<IdentifierExpression *>(term());

    //    if (!id)
    //        error("identifier expected");

    //    e = new ArrowExpression(e, id);
    //}

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

    //    else
    if (check(tInteger)) {
        e = Expression::Literal(new ValueObject(fromString<int>(token->getText())));
        getToken();
    } else if (check(tFloat)) {
        e = Expression::Literal(new ValueObject(fromString<double>(token->getText())));
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

        Expression *condition = term(), *body = assign(), *elseBody = 0;

        if (accept(tElse))
            elseBody = assign();
        else if (check(tElif)) {
            token->setId(tIf);
            elseBody = term();
        }

        e = id == tIf ? Expression::If(condition, body, elseBody) : Expression::While(condition, body, elseBody);
    } else if (accept(tForever))
        e = Expression::While(Expression::Literal(/*Runtime::getTrue()*/ 0), assign(), 0);
    //else if (accept(tFor)) {
    //    if (!accept(tLPar))
    //        error("left parenthesis expected");
    //
    //    list<Expression *> expressions = ((BlockExpression *)expr())->getExpressions();
    //
    //    if (!accept(tRPar))
    //        error("unmatched parentheses");
    //    if (expressions.size() != 3)
    //        error("three expressions expected");
    //
    //    list<Expression *>::iterator i = expressions.begin();
    //    e = new ForExpression(*i++, *i++, *i++, assign());
    //}
    else if (accept(tDo)) {
        Expression *body = assign();
        if (!accept(tWhile))
            error("while expected");
        e = Expression::Do(body, term());
    }

    //else if (accept(tReturn))
    //    e = new ReturnExpression(check(tRPar) || check(tRBrace) || check(tEnd) || accept(tSemi) ? 0 : assign());

    //else if (accept(tBreak))
    //    e = new BreakExpression(check(tRPar) || check(tRBrace) || check(tEnd) || accept(tSemi) ? 0 : assign());

    //else if (accept(tContinue))
    //    e = new ExceptionExpression(new ContinueException);

    else if (accept(tTrue))
        e = Expression::Literal(/*Runtime::getTrue()*/ 0);
    else if (accept(tFalse))
        e = Expression::Literal(/*Runtime::getFalse()*/ 0);
    else if (accept(tNull))
        e = Expression::Literal(/*Runtime::getNull()*/ 0);
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
    //} else if (accept(tClass)) {
    //    IdentifierExpression *name = 0;
    //    Expression *superClass = 0, *body;

    //    if (check(tId) || check(tColon))
    //        name = (IdentifierExpression *)term();
    //    if (accept(tLt))
    //        superClass = term();
    //    body = term();
    //    if (dynamic_cast<BlockExpression *>(body))
    //        ((BlockExpression *)body)->disableChildContext();

    //    e = new ClassExpression(name, superClass, body);
    //}

    //else if(accept(tTry)) {}

    else if (accept(tLPar)) {
        e = expr();

        if (!accept(tRPar))
            error("unmatched parentheses");
    } else if (accept(tLBrace)) {
        list<Expression *> expressions;

        while (!check(tRBrace) && !check(tEnd))
            expressions << expr();

        if (!accept(tRBrace))
            error("unmatched braces");

        e = Expression::Block(expressions);
    }

    else if (check(tEnd))
        error("unexpected end of expression");
    else if (check(tUnknown))
        error("unknown token '" + token->getText() + "'");
    else
        error("unexpected token '" + token->getText() + "'");

    return e;
}
}
