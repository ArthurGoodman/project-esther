#include "common/token.h"

#include "common/utility.h"

namespace es {

Token::Token()
    : id(-1)
    , text("") {
}

Token::Token(int id, const std::string &text)
    : id(id)
    , text(text) {
}

int Token::getId() const {
    return id;
}

void Token::setId(int id) {
    this->id = id;
}

std::string Token::getText() const {
    return text;
}

Token &Token::operator=(int id) {
    this->id = id;
    return *this;
}

Token &Token::operator+=(char c) {
    text += c;
    return *this;
}

bool Token::operator==(int id) const {
    return this->id == id;
}

bool Token::operator!=(int id) const {
    return this->id != id;
}

Position Token::getPosition() const {
    return pos;
}

void Token::setPosition(Position pos) {
    this->pos = pos;
}

std::string Token::inspect() const {
    return Utility::format("\"%s\" (%i, %i, %i)", text.c_str(), pos.getOffset(), pos.getLine(), pos.getColumn());
}
}
