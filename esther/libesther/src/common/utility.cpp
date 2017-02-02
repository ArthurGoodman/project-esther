#include "common/utility.h"

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

std::string Utility::expandTabs(const std::string &str) {
    std::string result;

    for (int i = 0, c = 0; i < (int)str.size(); i++)
        if (str[i] == '\t') {
            int delta = c % tabSize ? c % tabSize : tabSize;
            c += delta;
            result.insert(result.size(), delta, ' ');
        } else {
            result += str[i];

            if (str[i] == '\n')
                c = 0;
            else
                c++;
        }

    return result;
}

uint Utility::ceilToPowerOf2(uint n) {
    return 1 << (sizeof(n) * 8 - __builtin_clz(n - 1));
}
