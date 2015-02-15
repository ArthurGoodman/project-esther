#include "defaultlexer.h"

#include "tokens.h"
#include "lexicalerror.h"
#include "logger.h"
#include "utility.h"

// Lexemes:

vector<string> DefaultLexer::operators = {
#define X(a, b) b,
#include "operators.def"
#undef X
    ""};

vector<string> DefaultLexer::keywords = {
#define X(a, b) b,
#include "keywords.def"
#undef X
    ""};

#if DEBUG_LEXER
// This is used in logs.
vector<string> DefaultLexer::tokenTypes = {
#define X(a, b) #a,
#include "operators.def"
#include "keywords.def"
#include "othertokens.def"
#undef X
    ""};
#endif

Tokens &DefaultLexer::lex(const string &source) {
    // Initialize:
    this->source = &source;
    pos = 0;
    line = column = 1;

    tokens.clear();

    do { // Build the list of tokens.
        scan();
        tokens << token;

#if DEBUG_LEXER
        Logger::setActiveLog("lexer");

        Logger::write(tokenTypes[token.getId()]);
        Logger::write(" : \"" + token.getText() + "\"");
        Logger::write(" (");
        Logger::write(token.getPos().offset);
        Logger::write(", ");
        Logger::write(token.getPos().line);
        Logger::write(", ");
        Logger::write(token.getPos().column);
        Logger::write(")\n");
#endif
    } while (token != tEnd);

    return tokens;
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
            pos++;

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
                    error((string) "invalid escape sequence '\\" + at(pos) + "'", token.getText().size() + 1);
                }

                ++pos;
            } else
                token += at(pos++);
        }

        if (at(pos) != type)
            error("invalid string constant");
        else
            ++pos;
    } else if (Utility::isDigit(at(pos))) { // Numbers.
        token = tInteger;

        do
            token += at(pos++);
        while (Utility::isDigit(at(pos))); // Integral part.

        // Fractional part:
        if (at(pos) == '.' && Utility::isDigit(at(pos + 1))) {
            token = tFloat;

            do
                token += at(pos++);
            while (Utility::isDigit(at(pos)));
        }

        // Scientific notation:
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
    } else if (Utility::isLetter(at(pos))) { // Identifiers and keywords.
        do
            token += at(pos++);
        while (Utility::isLetterOrDigit(at(pos)));

        vector<string>::iterator i;

        if ((i = find(keywords.begin(), keywords.end(), token.getText())) != keywords.end())
            token = tKeywordMarker + distance(keywords.begin(), i);
        else
            token = tId;
    } else { // Operators and unknown tokens.
        vector<string>::iterator i;

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

void DefaultLexer::skipSpaces() {
    while (Utility::isSpace(at(pos))) {
        pos++;
        column++;
        if (at(pos - 1) == '\n') {
            line++;
            column = 1;
        }
    }
}

const char &DefaultLexer::at(int pos) {
    return (*source)[pos];
}
