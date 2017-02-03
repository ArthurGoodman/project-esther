#pragma once

#include <list>

#include "common/position.h"

class Token {
    int id;
    std::string text;
    Position pos;

public:
    Token();
    Token(int id, const std::string &text);

    int getId() const;
    void setId(int id);

    std::string getText() const;

    Token &operator=(int id);
    Token &operator+=(char c);

    bool operator==(int id) const;
    bool operator!=(int id) const;

    Position getPosition() const;
    void setPosition(Position pos);

    std::string inspect() const;
};

typedef std::list<Token> Tokens;
