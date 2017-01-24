#include "parser.h"

#include "common.h"
#include "expression.h"
#include "syntaxerror.h"
#include "tokens.h"
#include "variant.h"
#include "utility.h"
#include "runtime.h"
#include "context.h"
#include "class.h"
#include "function.h"

Expression *Parser::parse(Context *context, Tokens &tokens) {
    this->context = context;
    this->tokens.swap(tokens);
    token = this->tokens.begin();

    std::list<Expression *> nodes;

    while (!check(tEnd))
        nodes << expr();

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

std::list<Expression *> Parser::parseBlock() {
    std::list<Expression *> nodes;

    while (!check(tRBrace) && !check(tEnd))
        nodes << expr();

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

Expression *Parser::parseDot(Expression *e) {
    if (!check(tDollar) && !check(tLPar) && !check(tLBrace) && !check(tEnd))
        token->setId(tId);

    if (check(tId) || accept(tDollar)) {
        const std::string &name = token->getText();
        getToken();

        if (accept(tAssign))
            e = Expression::AttributeAssignment(e, name, logicOr());
        else if (accept(tLPar)) {
            const std::list<Expression *> &list = check(tRPar) ? std::list<Expression *>() : parseList();
            e = Expression::DirectCall(e, name, list);

            if (!accept(tRPar))
                error("unmatched parentheses");
        } else
            e = Expression::Attribute(e, name);
    } else {
        Expression *body = term();

        if (accept(tAssign))
            e = Expression::DirectCall(Expression::ContextResolution(e, body), "=", { logicOr() });
        else if (accept(tLPar)) {
            const std::list<Expression *> &list = check(tRPar) ? std::list<Expression *>() : parseList();
            e = Expression::ContextCall(e, body, list);

            if (!accept(tRPar))
                error("unmatched parentheses");
        } else
            e = Expression::ContextResolution(e, body);
    }

    return e;
}

Expression *Parser::parseIdentifier() {
    Expression *e = nullptr;

    if (check(tId)) {
        e = Expression::Literal(token->getText());
        getToken();
    } else if (accept(tDollar)) {
        if (check(tLPar) || check(tLBrace) || check(tEnd))
            e = term();
        else {
            e = Expression::Literal(token->getText());
            getToken();
        }
    }

    return e;
}

Expression *Parser::expr() {
    Expression *e = logicOr();

    while (true) {
        if (accept(tAssign))
            e = Expression::DirectCall(e, "=", { logicOr() });
        // TODO: get rid of this, this is terrible
        else if (accept(tPlusAssign))
            e = Expression::DirectCall(e, "=", { Expression::DirectCall(e, "+", { logicOr() }) });
        else if (accept(tMinusAssign))
            e = Expression::DirectCall(e, "=", { Expression::DirectCall(e, "-", { logicOr() }) });
        else if (accept(tMultiplyAssign))
            e = Expression::DirectCall(e, "=", { Expression::DirectCall(e, "*", { logicOr() }) });
        else if (accept(tDivideAssign))
            e = Expression::DirectCall(e, "=", { Expression::DirectCall(e, "/", { logicOr() }) });
        else if (accept(tModAssign))
            e = Expression::DirectCall(e, "=", { Expression::DirectCall(e, "%", { logicOr() }) });
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
            e = Expression::DirectCall(e, "==", { relation() });
        else if (accept(tNe))
            e = Expression::DirectCall(e, "!=", { relation() });
        else
            break;
    }

    return e;
}

Expression *Parser::relation() {
    Expression *e = addSub();

    while (true) {
        if (accept(tLt))
            e = Expression::DirectCall(e, "<", { addSub() });
        else if (accept(tGt))
            e = Expression::DirectCall(e, ">", { addSub() });
        else if (accept(tLe))
            e = Expression::DirectCall(e, "<=", { addSub() });
        else if (accept(tGe))
            e = Expression::DirectCall(e, ">=", { addSub() });
        else
            break;
    }

    return e;
}

Expression *Parser::addSub() {
    Expression *e = mulDiv();

    while (true) {
        if (accept(tPlus))
            e = Expression::DirectCall(e, "+", { mulDiv() });
        else if (accept(tMinus))
            e = Expression::DirectCall(e, "-", { mulDiv() });
        else
            break;
    }

    return e;
}

Expression *Parser::mulDiv() {
    Expression *e = power();

    while (true) {
        if (accept(tMultiply))
            e = Expression::DirectCall(e, "*", { power() });
        else if (accept(tDivide))
            e = Expression::DirectCall(e, "/", { power() });
        else if (accept(tMod))
            e = Expression::DirectCall(e, "%", { power() });
        else
            break;
    }

    return e;
}

Expression *Parser::power() {
    Expression *e = negate();

    while (true) {
        if (accept(tPower))
            e = Expression::DirectCall(e, "**", { negate() });
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
        e = Expression::DirectCall(Expression::Literal('\0'), "+", { suffix() });
    else if (accept(tMinus))
        e = Expression::DirectCall(Expression::Literal('\0'), "-", { suffix() });
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
        if (accept(tLPar)) {
            const std::list<Expression *> &list = check(tRPar) ? std::list<Expression *>() : parseList();
            e = Expression::DynamicCall(e, list);

            if (!accept(tRPar))
                error("unmatched parentheses");
        } else if (accept(tLBracket)) {
            const std::list<Expression *> &list = check(tRBracket) ? std::list<Expression *>() : parseList();
            e = Expression::DirectCall(e, "[]", list);

            if (!accept(tRBracket))
                error("unmatched brackets");
        } else if (accept(tDot))
            e = parseDot(e);
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
        else if (accept(tLPar)) {
            const std::list<Expression *> &list = check(tRPar) ? std::list<Expression *>() : parseList();
            e = Expression::Call(name, list);

            if (!accept(tRPar))
                error("unmatched parentheses");
        } else
            e = Expression::Identifier(name);
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
        e = Expression::Constant(context->getRuntime()->getTrue());
    else if (accept(tFalse))
        e = Expression::Constant(context->getRuntime()->getFalse());
    else if (accept(tNull))
        e = Expression::Constant(context->getRuntime()->getNull());

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

        Expression *superclass = accept(tLt) ? expr() : Expression::Constant(context->getRuntime()->getObjectClass());

        e = Expression::ContextResolution(Expression::ClassDefinition(name, superclass), Expression::Block({ term(), Expression::Self() }), true);

        if (!name.empty())
            e = Expression::LocalAssignment(name, e);
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
        if (check(tLBrace))
            e = Expression::DirectCall(Expression::Constant(context->getRuntime()->getObjectClass()), "new", {});
        else {
            if (check(tId) || accept(tDollar)) {
                e = Expression::Identifier(token->getText());
                getToken();
            } else
                e = term();

            std::list<Expression *> args;

            if (accept(tLPar)) {
                args = check(tRPar) ? std::list<Expression *>() : parseList();

                if (!accept(tRPar))
                    error("unmatched parentheses");
            }

            e = Expression::DirectCall(e, "new", args);
        }

        if (check(tLBrace))
            e = Expression::ContextResolution(e, Expression::Block({ term(), Expression::Self() }), true);
    }

    else if (accept(tAt))
        e = parseDot(Expression::Self());

    else if (accept(tLPar)) {
        e = expr();

        if (!accept(tRPar))
            error("unmatched parentheses");
    } else if (accept(tLBrace)) {
        const std::list<Expression *> &nodes = parseBlock();
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
