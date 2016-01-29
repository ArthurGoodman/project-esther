#pragma once

#include <list>

#include "position.h"

class Token {
    int id;
    std::string text;
    Position position;

public:
    Token();
    Token(int id, const std::string &text);

    int getId();
    void setId(int getId);

    std::string getText();

    Token &operator=(int getId);
    Token &operator+=(char c);

    bool operator==(int getId);
    bool operator!=(int getId);

    Position getPosition();
    void setPosition(Position position);
};

typedef std::list<Token> Tokens;
