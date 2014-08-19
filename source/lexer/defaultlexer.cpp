#include "defaultlexer.h"

#include "lexicalerror.h"
#include "runtime.h"

namespace Esther {

list<string> DefaultLexer::operators, DefaultLexer::keywords;

Tokens DefaultLexer::lex()
{
    // Initialize:
    source = new string;
    *source = Runtime::source();
    pos = 0; line = column = 1;

    tokens.clear();

    do // Form the list of tokens.
    {
        scan(); tokens << token;

        //cout << token.getId() << " : \"" << token.getText() << "\""
        //     << " (" << token.getPos().offset << "," << token.getPos().line << "," << token.getPos().column << ")\n";
    }
    while(token != tEnd);

    return tokens;
}

void DefaultLexer::initialize()
{
    // Lexemes:

    operators << "+" << "-" << "*" << "/" << "%"
              << "<" << ">" << "<=" << ">=" << "==" << "!="
              << "&" << "|" << "^" << "!"
              << "=" << "+=" << "-=" << "*=" << "/=" << "%="
              << "--" << "++"
              << "." << "->" << "," << ":" << "@" << "$" << ";"
              << "(" << "[" << "{" << ")" << "]" << "}";

    keywords << "if" << "else" << "elif" << "while" << "for" << "do" << "forever"
             << "true" << "false" << "null" << "self" << "super" << "context"
             << "continue" << "break" << "return" << "include"
             << "class" << "static" << "method" << "function"
             << "try" << "throw" << "catch";
}

void DefaultLexer::error(string msg, int delta)
{
    // Delta is used when the position of the token needs to be corrected.
    ErrorException *e = new LexicalError(msg, token.getPos().shifted(delta));
    e->raise();
}

void DefaultLexer::scan()
{
    token = Token(); // Clear current token.

    skipSpaces();

    while((*source)[pos] == '/' && (*source)[pos + 1] == '/') //Comment.
    {
        while((*source)[pos] && (*source)[pos] != '\n') ++pos;
        skipSpaces();
    }

    token.setPos(Position(pos, line, column));

    if(!(*source)[pos]) token = tEnd;
    else if((*source)[pos] == '\'' || (*source)[pos] == '"') // String literals.
    {
        char type = (*source)[pos++]; token = type == '"' ? tComplexString : tString;

        while((*source)[pos] && (*source)[pos] != type)
        {
            if((*source)[pos] == '\n') break;

            if((*source)[pos] == '\\') // Escape sequences.
            {
                switch((*source)[++pos])
                {
                case 'n': token += '\n'; break;
                case 't': token += '\t'; break;
                case '\\': token += '\\'; break;
                case '\'': token += '\''; break;
                case '"': token += '"'; break;
                case '\n': break;

                default: error((string)"invalid escape sequence '\\" + (*source)[pos] + "'", token.getText().size() + 1);
                }

                ++pos;
            }
            else token += (*source)[pos++];
        }

        if((*source)[pos] != type) error("invalid string constant"); else ++pos;
    }
    else if(isDigit((*source)[pos])) // Numbers.
    {
        token = tInteger; do token += (*source)[pos++]; while(isDigit((*source)[pos])); // Integral part.

        // Fractional part:
        if((*source)[pos] == '.' && isDigit((*source)[pos + 1]))
        { token = tFloat; do token += (*source)[pos++]; while(isDigit((*source)[pos])); }

        // Scientific notation:
        if((toLower((*source)[pos]) == 'e') && (isDigit((*source)[pos + 1]) || (isSign((*source)[pos + 1]) && isDigit((*source)[pos + 2]))))
        {
            token += (*source)[pos++];

            if((isSign((*source)[pos])) && isDigit((*source)[pos + 1])) do token += (*source)[pos++]; while(isDigit((*source)[pos]));
            else while(isDigit((*source)[pos])) token += (*source)[pos++];
        }
    }
    else if(isLetter((*source)[pos]) || (*source)[pos] == '_') // Identifiers and keywords.
    {
        do token += (*source)[pos++]; while(isLetterOrDigit((*source)[pos]) || (*source)[pos] == '_');

        list<string>::iterator i;

        if((i = find(keywords.begin(), keywords.end(), token.getText())) != keywords.end())
            token = tIf + distance(keywords.begin(), i); else token = tId;
    }
    else // Operators and other tokens.
    {
        token += (*source)[pos++];

        if(string("<>=!+-*/%").find(token.getText()) + 1 && (*source)[pos] == '=') token += (*source)[pos++]; // ?= operators.
        else if(token.getText() == "-" && (*source)[pos] == '>') // Arrow.
            token += (*source)[pos++];

        list<string>::iterator i;

        if((i = find(operators.begin(), operators.end(), token.getText())) != operators.end())
            token = distance(operators.begin(), i); else token = tUnknown;
    }

    column += token.getText().length();
}

void DefaultLexer::skipSpaces()
{
    while(isSpace((*source)[pos]))
    {
        ++pos; ++column;
        if((*source)[pos - 1] == '\n') { ++line; column = 1; }
    }
}

}
