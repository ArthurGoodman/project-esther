#pragma once
#include <common.h>
#include <debug.h>

#include "lexer.h"

namespace esther {

// Ids for all the lexemes:
// Ids have to be enumerated in the exact same order as lexemes are.
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
    tVar,

    tId,
    tInteger,
    tFloat,
    tString,
    tComplexString,
    tUnknown,
    tEnd
};

class DefaultLexer : public Lexer {
    static string operators[];
    static string keywords[];

#if DEBUG_LEXER
    static string tokenTypes[];
#endif

    Tokens tokens; // List of tokens, that the lexer produces.

    const string *source;
    Token token;           // Current token.
    int pos, line, column; // Current position of the lexer.

public:
    Tokens &lex(const string &source);

private:
    template <int N>
    static int count(string (&)[N]);

    void error(string msg, int shift = 0); // Handle lexical errors.
    void scan();                           // Scan code for the next lexeme.
    void skipSpaces();
    const char &at(int pos);
};

// Count elements of an array of strings.
template <int N>
int DefaultLexer::count(string (&)[N]) {
    return N;
}
}
