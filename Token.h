#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

using namespace std;
enum class TokenType {
    COMMA,
    COLON,
    COLON_DASH,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    EOF_TYPE,
    UNDEFINED
};

class Token
{
private:
    TokenType type;
    string description;
    int line;
    string typeName;
public:
    Token(TokenType type, string description, int line);
    string toString();
    TokenType getTokenType();
    string getValue();


};

#endif // TOKEN_H