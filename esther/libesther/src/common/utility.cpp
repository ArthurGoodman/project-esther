#include "utility.h"

#include <cstdarg>

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

uint32_t Utility::ceilToPowerOf2(uint32_t n) {
    return 1 << (sizeof(n) * 8 - __builtin_clz(n - 1));
}

std::string Utility::vformat(const char *fmt, va_list ap) {
    size_t size = 1024;
    char stackbuf[size];

    std::vector<char> dynamicbuf;
    char *buf = &stackbuf[0];
    va_list ap_copy;

    while (true) {
        va_copy(ap_copy, ap);
        int needed = vsnprintf(buf, size, fmt, ap);
        va_end(ap_copy);

        if (needed <= (int)size && needed >= 0)
            return std::string(buf, (size_t)needed);

        size = needed > 0 ? needed + 1 : size * 2;
        dynamicbuf.resize(size);
        buf = &dynamicbuf[0];
    }
}

std::string Utility::format(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    std::string buf = vformat(fmt, ap);
    va_end(ap);
    return buf;
}
