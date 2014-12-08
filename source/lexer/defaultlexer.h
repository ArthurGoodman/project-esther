#pragma once
#include <common.h>

#include "lexer.h"

namespace Esther {

// Ids for all the lexemes:
// Ids have to be enumerated in the exact same sequence as lexemes are.
enum {
    tNone = Token::invalidTokenId,

    tPlus,
    tMinus,
    tMultiply,
    tDivide,
    tMod,
    tLt,
    tGt,
    tLe,
    tGe,
    tEq,
    tNe,
    tAnd,
    tOr,
    tXor,
    tNot,
    tAssign,
    tPlusAssign,
    tMinusAssign,
    tMultiplyAssign,
    tDivideAssign,
    tModAssign,
    tDec,
    tInc,
    tDot,
    tArrow,
    tComma,
    tColon,
    tAt,
    tDollar,
    tSemi,
    tLPar,
    tLBracket,
    tLBrace,
    tRPar,
    tRBracket,
    tRBrace,

    tIf,
    tElse,
    tElif,
    tWhile,
    tFor,
    tDo,
    tForever,
    tTrue,
    tFalse,
    tNull,
    tSelf,
    tSuper,
    tContext,
    tContinue,
    tBreak,
    tReturn,
    tInclude,
    tClass,
    tStatic,
    tMethod,
    tFunction,
    tTry,
    tThrow,
    tCatch,

    tId,
    tInteger,
    tFloat,
    tString,
    tComplexString,
    tUnknown,
    tEnd
};

class DefaultLexer : public Lexer {
    Tokens tokens; // List of tokens, that the lexer produces.

    const string *source;
    Token token;           // Current token.
    int pos, line, column; // Current position of the lexer.

    static list<string> operators, keywords;

public:
    Tokens lex(const string &source);

    static void initialize();

    static const list<string> &getOperators();
    static const list<string> &getKeywords();

private:
    void error(string msg, int shift = 0); // Handle lexical errors.
    void scan();                           // Scan code for the next lexeme.
    void skipSpaces();
    const char &at(int pos);
};
}
