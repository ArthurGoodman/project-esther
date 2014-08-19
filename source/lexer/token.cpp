#include "token.h"

namespace Esther {

Token::Token() : id(invalidTokenId), text("") {}
Token::Token(int id, const string &text) : id(id), text(text) {}

int Token::getId() { return id; }
void Token::setId(int id) { this->id = id; }

string Token::getText() { return text; }

Position Token::getPos() { return pos; }
void Token::setPos(Position pos) { this->pos = pos; }

Token &Token::operator =(int id) { this->id = id; return *this; }
Token &Token::operator +=(char c) { text += c; return *this; }

bool Token::operator ==(int id) { return this->id == id; }
bool Token::operator !=(int id) { return this->id != id; }

}
