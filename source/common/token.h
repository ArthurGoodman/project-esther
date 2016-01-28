#pragma once
#include "common.h"

#include "position.h"

class Token {
    int id;
    string text;
    Position position;

public:
    Token();
    Token(int id, const string &text);

    int getId();
    void setId(int getId);

    string getText();

    Token &operator=(int getId);
    Token &operator+=(char c);

    bool operator==(int getId);
    bool operator!=(int getId);

    Position getPosition();
    void setPosition(Position position);
};

typedef list<Token> Tokens;
