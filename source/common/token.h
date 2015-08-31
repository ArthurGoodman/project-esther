#pragma once
#include "common.h"

#include "positionedobject.h"

// A lexeme with additional information.
class Token : public PositionedObject {
    int id;
    string text;

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
};

typedef list<Token> Tokens;
