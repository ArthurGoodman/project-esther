#include "defaultlexer.h"

#include "lexicalerror.h"

namespace Esther {

list<string> DefaultLexer::operators, DefaultLexer::keywords;

Tokens DefaultLexer::lex(const string &source) {
    // Initialize:
    this->source = &source;
    pos = 0;
    line = column = 1;

    tokens.clear();

    do { // Form the list of tokens.
        scan();
        tokens << token;

        cout << token.getId() << " : \"" << token.getText() << "\""
             << " (" << token.getPos().offset << "," << token.getPos().line << "," << token.getPos().column << ")\n";
    } while (token != tEnd);

    return tokens;
}

void DefaultLexer::initialize() {
    // Lexemes:

    operators << "+"
              << "-"
              << "*"
              << "/"
              << "%"
              << "<"
              << ">"
              << "<="
              << ">="
              << "=="
              << "!="
              << "&"
              << "|"
              << "^"
              << "!"
              << "="
              << "+="
              << "-="
              << "*="
              << "/="
              << "%="
              << "--"
              << "++"
              << "."
              << "->"
              << ","
              << ":"
              << "@"
              << "$"
              << ";"
              << "("
              << "["
              << "{"
              << ")"
              << "]"
              << "}";

    keywords << "if"
             << "else"
             << "elif"
             << "while"
             << "for"
             << "do"
             << "forever"
             << "true"
             << "false"
             << "null"
             << "self"
             << "super"
             << "context"
             << "continue"
             << "break"
             << "return"
             << "include"
             << "class"
             << "static"
             << "method"
             << "function"
             << "try"
             << "throw"
             << "catch";
}

const list<string> &DefaultLexer::getOperators() {
    return operators;
}

const list<string> &DefaultLexer::getKeywords() {
    return keywords;
}

void DefaultLexer::error(string msg, int delta) {
    // Delta is used when the position of the token needs to be corrected.
    ErrorException *e = new LexicalError(msg, token.getPos().shifted(delta));
    e->raise();
}

void DefaultLexer::scan() {
    token = Token(); // Clear current token.

    skipSpaces();

    while (at(pos) == '/' && at(pos + 1) == '/') { // Comment.
        while (at(pos) && at(pos) != '\n')
            ++pos;

        skipSpaces();
    }

    token.setPos(Position(pos, line, column));

    if (!at(pos))
        token = tEnd;

    else if (at(pos) == '\'' || at(pos) == '"') { // String literals.
        char type = at(pos++);

        token = type == '"' ? tComplexString : tString;

        while (at(pos) && at(pos) != type) {
            if (at(pos) == '\n')
                break;

            if (at(pos) == '\\') { // Escape sequences.
                switch (at(++pos)) {
                case 'n':
                    token += '\n';
                    break;
                case 't':
                    token += '\t';
                    break;
                case '\\':
                    token += '\\';
                    break;
                case '\'':
                    token += '\'';
                    break;
                case '"':
                    token += '"';
                    break;
                case '\n':
                    break;

                default:
                    error((string) "invalid escape sequence '\\" + at(pos) + "'",
                          token.getText().size() + 1);
                }

                ++pos;
            } else
                token += at(pos++);
        }

        if (at(pos) != type)
            error("invalid string constant");
        else
            ++pos;
    } else if (isDigit(at(pos))) { // Numbers.
        token = tInteger;

        do
            token += at(pos++);
        while (isDigit(at(pos))); // Integral part.

        // Fractional part:
        if (at(pos) == '.' && isDigit(at(pos + 1))) {
            token = tFloat;

            do
                token += at(pos++);
            while (isDigit(at(pos)));
        }

        // Scientific notation:
        if ((toLower(at(pos)) == 'e') && (isDigit(at(pos + 1)) || (isSign(at(pos + 1)) && isDigit(at(pos + 2))))) {
            token += at(pos++);

            if ((isSign(at(pos))) && isDigit(at(pos + 1)))
                do
                    token += at(pos++);
                while (isDigit(at(pos)));
            else
                while (isDigit(at(pos)))
                    token += at(pos++);
        }
    } else if (isLetter(at(pos)) || at(pos) == '_') { // Identifiers and keywords.
        do
            token += at(pos++);
        while (isLetterOrDigit(at(pos)) || at(pos) == '_');

        list<string>::iterator i;

        if ((i = find(keywords.begin(), keywords.end(), token.getText())) != keywords.end())
            token = tIf + distance(keywords.begin(), i);
        else
            token = tId;
    } else { // Operators and other tokens.
        token += at(pos++);

        if (string("<>=!+-*/%").find(token.getText()) + 1 && at(pos) == '=')
            token += at(pos++);                            // ?= operators.
        else if (token.getText() == "-" && at(pos) == '>') // Arrow.
            token += at(pos++);

        list<string>::iterator i;

        if ((i = find(operators.begin(), operators.end(), token.getText())) !=
            operators.end())
            token = distance(operators.begin(), i);
        else
            token = tUnknown;
    }

    column += token.getText().length();
}

void DefaultLexer::skipSpaces() {
    while (isSpace(at(pos))) {
        ++pos;
        ++column;
        if (at(pos - 1) == '\n') {
            ++line;
            column = 1;
        }
    }
}

const char &DefaultLexer::at(int pos) {
    return (*source)[pos];
}
}
