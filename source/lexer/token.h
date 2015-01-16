#pragma once
#include <common.h>

#include "position.h"

namespace esther {

// A lexeme with additional information.
class Token {
    int id;
    string text;
    Position pos; // Position of the lexeme in code.

public:
    static const int invalidTokenId = -1;

public:
    Token();
    Token(int id, const string &text);

    int getId();
    void setId(int getId);

    string getText();

    Position getPos();
    void setPos(Position getPos);

    Token &operator=(int getId);
    Token &operator+=(char c);

    bool operator==(int getId);
    bool operator!=(int getId);
};

typedef list<Token> Tokens;
}
