#include "utility.h"

char Utility::toLower(char c) {
    return c < 'A' || c > 'Z' ? c : c + 'a' - 'A';
}

char Utility::toUpper(char c) {
    return c < 'a' || c > 'z' ? c : c + 'A' - 'a';
}

bool Utility::isSign(char c) {
    return c == '+' || c == '-';
}

bool Utility::isSpace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

bool Utility::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Utility::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Utility::isLetterOrDigit(char c) {
    return isLetter(c) || isDigit(c);
}
