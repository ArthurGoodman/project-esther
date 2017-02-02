#pragma once

#include <list>

#include "common/position.h"

class Token {
    int id;
    std::string text;
    Position position;

public:
    Token();
    Token(int id, const std::string &text);

    int getId() const;
    void setId(int getId);

    std::string getText() const;

    Token &operator=(int getId);
    Token &operator+=(char c);

    bool operator==(int getId) const;
    bool operator!=(int getId) const;

    Position getPosition() const;
    void setPosition(Position position);
};

typedef std::list<Token> Tokens;
