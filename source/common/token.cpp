#include "token.h"

Token::Token()
    : id(-1), text("") {
}

Token::Token(int id, const string &text)
    : id(id), text(text) {
}

int Token::getId() {
    return id;
}

void Token::setId(int id) {
    this->id = id;
}

string Token::getText() {
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

bool Token::operator==(int id) {
    return this->id == id;
}

bool Token::operator!=(int id) {
    return this->id != id;
}

Position Token::getPosition() {
    return position;
}

void Token::setPosition(Position position) {
    this->position = position;
}
