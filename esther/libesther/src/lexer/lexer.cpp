#include "lexer.h"

#include <algorithm>

#include "common/definitions/tokens.h"
#include "common/logger.h"
#include "common/utility.h"
#include "exception/lexicalerror.h"

std::vector<std::string> Lexer::operators = {
#define X(a, b) b,
#include "common/definitions/operators.def"
#undef X
};

std::vector<std::string> Lexer::keywords = {
#define X(a, b) b,
#include "common/definitions/keywords.def"
#undef X
};

#if DEBUG_LEXER
std::vector<std::string> Lexer::tokenTypes = {
#define X(a, b) #a,
#include "common/definitions/operators.def"
#include "common/definitions/keywords.def"
#include "common/definitions/othertokens.def"
#undef X
};
#endif

Tokens &Lexer::lex(const std::string &source) {
    this->source = &source;
    pos = 0;
    line = column = 1;

    tokens.clear();

    do {
        scan();
        tokens << token;

#if DEBUG_LEXER
        Logger::setActiveLog("lexer");

        Logger::write(tokenTypes[token.getId()]);
        Logger::write(" : \"" + token.getText() + "\"");
        Logger::write(" (");
        Logger::write(token.getPosition().getOffset());
        Logger::write(", ");
        Logger::write(token.getPosition().getLine());
        Logger::write(", ");
        Logger::write(token.getPosition().getColumn());
        Logger::write(")\n");
#endif
    } while (token != tEnd);

    return tokens;
}

void Lexer::error(const std::string &msg, int delta) {
    throw new LexicalError(msg, token.getPosition().shifted(delta));
}

void Lexer::scan() {
    token = Token();

    skipSpaces();

    if (at(pos) == '/' && at(pos + 1) == '/') {
        while (at(pos) == '/' && at(pos + 1) == '/') {
            while (at(pos) && at(pos) != '\n')
                pos++;

            skipSpaces();
        }
    }

    token.setPosition(Position(pos, line, column));

    if (!at(pos))
        token = tEnd;
    else if (at(pos) == '\'' || at(pos) == '"') {
        char type = at(pos++);
        column++;

        token = type == '\'' ? tString : tComplexString;

        while (at(pos) && at(pos) != type) {
            if (at(pos) == '\n')
                break;

            if (at(pos) == '\\') {
                switch (at(++pos)) {
                case 'n':
                    token += '\n';
                    column += 2;
                    break;
                case 't':
                    token += '\t';
                    column += 2;
                    break;
                case '0':
                    token += '\0';
                    column += 2;
                    break;
                case '\\':
                    token += '\\';
                    column += 2;
                    break;
                case '\'':
                    token += '\'';
                    column += 2;
                    break;
                case '"':
                    token += '"';
                    column += 2;
                    break;
                case '\n':
                    line++;
                    column = 1;
                    break;

                default:
                    token.setPosition(Position(pos, line, column));
                    error(static_cast<std::string>("invalid escape sequence '\\") + at(pos) + "'");
                }

                pos++;
            } else {
                token += at(pos++);
                column++;
            }
        }

        if (at(pos) != type)
            error("invalid string constant");

        pos++;
        column++;

        column -= token.getText().length();
    } else if (Utility::isDigit(at(pos))) {
        token = tInteger;

        do
            token += at(pos++);
        while (Utility::isDigit(at(pos)));

        if (at(pos) == '.' && Utility::isDigit(at(pos + 1))) {
            token = tFloat;

            do
                token += at(pos++);
            while (Utility::isDigit(at(pos)));
        }

        if ((Utility::toLower(at(pos)) == 'e') && (Utility::isDigit(at(pos + 1)) || (Utility::isSign(at(pos + 1)) && Utility::isDigit(at(pos + 2))))) {
            token += at(pos++);

            if ((Utility::isSign(at(pos))) && Utility::isDigit(at(pos + 1)))
                do
                    token += at(pos++);
                while (Utility::isDigit(at(pos)));
            else
                while (Utility::isDigit(at(pos)))
                    token += at(pos++);
        }
    } else if (Utility::isLetter(at(pos)) || at(pos) == '_') {
        do
            token += at(pos++);
        while (Utility::isLetterOrDigit(at(pos)) || at(pos) == '_');

        std::vector<std::string>::iterator i;

        if ((i = find(keywords.begin(), keywords.end(), token.getText())) != keywords.end())
            token = tKeywordMarker + distance(keywords.begin(), i);
        else
            token = tId;
    } else {
        std::vector<std::string>::iterator i;

        while (i != operators.end())
            for (i = operators.begin(); i != operators.end(); ++i)
                if (i->substr(0, token.getText().size() + 1) == token.getText() + at(pos)) {
                    token += at(pos++);
                    break;
                }

        if (!token.getText().empty() && (i = find(operators.begin(), operators.end(), token.getText())) != operators.end())
            token = tOperatorMarker + distance(operators.begin(), i);
        else {
            if (token.getText().empty())
                token += at(pos++);

            token = tUnknown;
        }
    }

    column += token.getText().length();
}

void Lexer::skipSpaces() {
    while (Utility::isSpace(at(pos))) {
        pos++;
        column++;
        if (at(pos - 1) == '\n') {
            line++;
            column = 1;
        }
    }
}

const char &Lexer::at(int pos) {
    return (*source)[pos];
}
