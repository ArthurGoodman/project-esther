#include "parser.h"

#include "common.h"
#include "expression.h"
#include "syntaxerror.h"
#include "variant.h"
#include "utility.h"
#include "esther.h"
#include "context.h"
#include "class.h"
#include "function.h"
#include "classclass.h"

Expression *Parser::parse(Esther *esther, Tokens &tokens) {
    this->esther = esther;
    this->tokens.swap(tokens);
    token = this->tokens.begin();

    std::list<Expression *> nodes;

    while (!check(tEnd)) {
        nodes << expr();

        if (!nodes.back())
            return nullptr;
    }

    Expression *e = nodes.empty() ? Expression::Empty() : nodes.size() == 1 ? nodes.front() : Expression::Block(nodes);

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

std::list<Expression *> Parser::block() {
    std::list<Expression *> nodes;

    while (!check(tRBrace) && !check(tEnd))
        nodes << expr();

    if (!accept(tRBrace))
        error("unmatched braces");

    return nodes;
}

std::list<Expression *> Parser::list() {
    std::list<Expression *> nodes;

    do
        nodes << logicOr();
    while (accept(tComma));

    return nodes;
}

Expression *Parser::binOper(Expression *left, const std::string &oper, Expression *right) {
    std::list<Expression *> nodes;

    nodes << Expression::Push(left);
    nodes << Expression::Push(Expression::Attribute(Expression::Stack(0), oper));
    nodes << Expression::Push(right);
    nodes << Expression::Call(Expression::Stack(1), Expression::Stack(2), 1);
    nodes << Expression::Pop(3);

    return Expression::Block(nodes);
}

Expression *Parser::assignOper(Expression *left, const std::string &oper, Expression *right) {
    std::list<Expression *> nodes;

    nodes << Expression::Push(left);
    nodes << Expression::Push(Expression::Attribute(Expression::Stack(0), oper));
    nodes << Expression::Push(Expression::Attribute(Expression::Stack(1), "="));
    nodes << Expression::Push(right);
    nodes << Expression::Push(Expression::Call(Expression::Stack(2), Expression::Stack(3), 1));
    nodes << Expression::Call(Expression::Stack(2), Expression::Stack(4), 1);
    nodes << Expression::Pop(5);

    return Expression::Block(nodes);
}

Expression *Parser::call(Expression *self, Expression *f, int closingBracketId) {
    std::list<Expression *> nodes;
    int args = 0;

    nodes << Expression::Push(self);
    nodes << Expression::Push(f);

    if (!check(closingBracketId))
        do {
            nodes << Expression::Push(logicOr());
            args++;
        } while (accept(tComma));

    if (!accept(closingBracketId))
        error("unmatched parentheses");

    nodes << Expression::Call(Expression::Stack(args), Expression::Stack(args + 1), args);
    nodes << Expression::Pop(args + 2);

    return Expression::Block(nodes);
}

Expression *Parser::dot(Expression *e) {
    if (!check(tDollar) && !check(tLPar) && !check(tLBrace) && !check(tEnd))
        token->setId(tId);

    if (check(tId) || accept(tDollar)) {
        const std::string &name = token->getText();
        getToken();

        if (accept(tAssign))
            e = Expression::AttributeAssignment(e, name, logicOr());
        else if (accept(tLPar))
            e = call(e, Expression::Attribute(Expression::Stack(0), name));
        else
            e = Expression::Attribute(e, name);
    } else {
        Expression *body = term();
        Expression *newObject = Expression::Call(Expression::Constant(esther->getClassClass()->getAttribute("new")), Expression::Constant(esther->getObjectClass()), 0);

        if (accept(tLPar))
            e = call(e, Expression::ContextResolution(Expression::Stack(0), body, newObject));
        else
            e = Expression::ContextResolution(e, body, newObject);
    }

    return e;
}

Expression *Parser::expr() {
    Expression *e = logicOr();

    while (true) {
        if (accept(tAssign))
            e = binOper(e, "=", logicOr());
        else if (accept(tPlusAssign))
            e = assignOper(e, "+", logicOr());
        else if (accept(tMinusAssign))
            e = assignOper(e, "-", logicOr());
        else if (accept(tMultiplyAssign))
            e = assignOper(e, "*", logicOr());
        else if (accept(tDivideAssign))
            e = assignOper(e, "/", logicOr());
        else if (accept(tModAssign))
            e = assignOper(e, "%", logicOr());
        else
            break;
    }

    accept(tSemi);

    return e;
}

Expression *Parser::logicOr() {
    Expression *e = logicAnd();

    while (true) {
        if (accept(tOr))
            e = Expression::Or(e, logicAnd());
        else
            break;
    }

    return e;
}

Expression *Parser::logicAnd() {
    Expression *e = equality();

    while (true) {
        if (accept(tAnd))
            e = Expression::And(e, equality());
        else
            break;
    }

    return e;
}

Expression *Parser::equality() {
    Expression *e = relation();

    while (true) {
        if (accept(tEq))
            e = binOper(e, "==", relation());
        else if (accept(tNe))
            e = binOper(e, "!=", relation());
        else
            break;
    }

    return e;
}

Expression *Parser::relation() {
    Expression *e = addSub();

    while (true) {
        if (accept(tLt))
            e = binOper(e, "<", addSub());
        else if (accept(tGt))
            e = binOper(e, ">", addSub());
        else if (accept(tLe))
            e = binOper(e, "<=", addSub());
        else if (accept(tGe))
            e = binOper(e, ">=", addSub());
        else
            break;
    }

    return e;
}

Expression *Parser::addSub() {
    Expression *e = mulDiv();

    while (true) {
        if (accept(tPlus))
            e = binOper(e, "+", mulDiv());
        else if (accept(tMinus))
            e = binOper(e, "-", mulDiv());
        else
            break;
    }

    return e;
}

Expression *Parser::mulDiv() {
    Expression *e = power();

    while (true) {
        if (accept(tMultiply))
            e = binOper(e, "*", power());
        else if (accept(tDivide))
            e = binOper(e, "/", power());
        else if (accept(tMod))
            e = binOper(e, "%", power());
        else
            break;
    }

    return e;
}

Expression *Parser::power() {
    Expression *e = negate();

    while (true) {
        if (accept(tPower))
            e = binOper(e, "**", negate());
        else
            break;
    }

    return e;
}

Expression *Parser::negate() {
    Expression *e = nullptr;

    if (accept(tNot))
        e = Expression::Not(preffix());
    else
        e = preffix();

    return e;
}

Expression *Parser::preffix() {
    Expression *e = nullptr;

    if (accept(tPlus))
        e = binOper(Expression::Literal('\0'), "+", suffix());
    else if (accept(tMinus))
        e = binOper(Expression::Literal('\0'), "-", suffix());
    //    else if (accept(tDec))
    //        e = Expression::PreDecrement(suffix());
    //    else if (accept(tInc))
    //        e = Expression::PreIncrement(suffix());
    else
        e = suffix();

    return e;
}

Expression *Parser::suffix() {
    Expression *e = term();

    while (check(tLPar) || check(tLBracket) || check(tDot)) {
        if (accept(tLPar))
            e = call(Expression::Self(), e);
        else if (accept(tLBracket))
            e = call(e, Expression::Attribute(Expression::Stack(0), "[]"), tRBracket);
        else if (accept(tDot))
            e = dot(e);
    }
    //    else if (realAccept(tDec))
    //        e = Expression::PostDecrement(e);
    //    else if (realAccept(tInc))
    //        e = Expression::PostIncrement(e);

    return e;
}

Expression *Parser::term() {
    Expression *e = nullptr;

    if (check(tId) || accept(tDollar)) {
        const std::string &name = token->getText();
        getToken();

        if (accept(tAssign))
            e = Expression::Assignment(name, logicOr());
        else if (accept(tLPar))
            e = call(Expression::Self(), Expression::Identifier(name));
        else
            e = Expression::Identifier(name);
    }

    else if (accept(tVar)) {
        if (!check(tId) && !accept(tDollar))
            error("identifier expected");

        const std::string &name = token->getText();
        getToken();

        e = Expression::LocalAssignment(name, accept(tAssign) ? logicOr() : Expression::Constant(esther->getNull()));
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

    else if (accept(tIf)) {
        Expression *condition, *body, *elseBody = nullptr;

        condition = expr();
        body = expr();

        if (accept(tElse))
            elseBody = expr();

        e = Expression::If(condition, body, elseBody);
    } else if (accept(tWhile)) {
        Expression *condition, *body;

        condition = expr();
        body = expr();

        e = Expression::Loop(condition, body);
    }

    else if (accept(tTrue))
        e = Expression::Constant(esther->getTrue());
    else if (accept(tFalse))
        e = Expression::Constant(esther->getFalse());
    else if (accept(tNull))
        e = Expression::Constant(esther->getNull());

    else if (accept(tSelf))
        e = Expression::Self();
    else if (accept(tHere))
        e = Expression::Here();

    else if (accept(tClass)) {
        std::string name;

        if (check(tId) || accept(tDollar)) {
            name = token->getText();
            getToken();
        }

        Expression *superclass = accept(tLt) ? expr() : Expression::Constant(esther->getObjectClass());

        std::list<Expression *> nodes;

        nodes << Expression::Push(Expression::ClassDefinition(name, superclass));
        nodes << Expression::ContextResolution(Expression::Stack(0), term());

        if (!name.empty())
            nodes << Expression::LocalAssignment(name, Expression::Stack(0));

        nodes << Expression::Pop(1);

        e = Expression::Block(nodes);
    }

    else if (accept(tFunction)) {
        std::string name;

        if (check(tId) || accept(tDollar)) {
            name = token->getText();
            getToken();
        }

        std::list<std::string> params;

        if (accept(tLPar) && !accept(tRPar)) {
            do {
                if (!check(tId))
                    error("identifier expected");

                params << token->getText();
                getToken();
            } while (accept(tComma));

            if (!accept(tRPar))
                error("unmatched parentheses");
        }

        e = Expression::FunctionDefinition(name, params, expr());

        if (!name.empty())
            e = Expression::LocalAssignment(name, e);
    }

    else if (accept(tNew)) {
        if (check(tLBrace)) {
            Expression *newObject = Expression::Call(Expression::Constant(esther->getClassClass()->getAttribute("new")), Expression::Constant(esther->getObjectClass()), 0);

            std::list<Expression *> nodes;

            nodes << Expression::Push(newObject);
            nodes << Expression::ContextResolution(Expression::Stack(0), term());
            nodes << Expression::Stack(0);
            nodes << Expression::Pop(1);

            e = Expression::Block(nodes);
        } else {
            if (check(tId) || accept(tDollar)) {
                e = Expression::Identifier(token->getText());
                getToken();
            } else
                e = term();

            std::list<Expression *> nodes;
            int args = 0;

            nodes << Expression::Push(e);
            nodes << Expression::Push(Expression::Attribute(Expression::Stack(0), "new"));

            if (accept(tLPar)) {
                if (!check(tRPar))
                    do {
                        nodes << Expression::Push(logicOr());
                        args++;
                    } while (accept(tComma));

                if (!accept(tRPar))
                    error("unmatched parentheses");
            }

            if (check(tLBrace)) {
                nodes << Expression::Push(Expression::Call(Expression::Stack(args), Expression::Stack(args + 1), args));
                nodes << Expression::ContextResolution(Expression::Stack(0), term());
                nodes << Expression::Stack(0);
                nodes << Expression::Pop(args + 3);
            } else {
                nodes << Expression::Call(Expression::Stack(args), Expression::Stack(args + 1), args);
                nodes << Expression::Pop(args + 2);
            }

            e = Expression::Block(nodes);
        }
    }

    else if (accept(tAt))
        e = dot(Expression::Self());

    else if (accept(tLPar)) {
        e = expr();

        if (!accept(tRPar))
            error("unmatched parentheses");
    } else if (accept(tLBrace)) {
        const std::list<Expression *> &nodes = block();
        e = nodes.empty() ? Expression::Empty() : nodes.size() == 1 ? nodes.front() : Expression::Block(nodes);
    }

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
