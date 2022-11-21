#include "Token.h"

std::string GetTypeName(TokenType type) {
    switch (type) {
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::COLON:
            return "COLON";
        case TokenType::COLON_DASH:
            return "COLON_DASH";
        case TokenType::PERIOD:
            return "PERIOD";
        case TokenType::Q_MARK:
            return "Q_MARK";
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::ADD:
            return "ADD";
        case TokenType::SCHEMES:
            return "SCHEMES";
        case TokenType::FACTS:
            return "FACTS";
        case TokenType::RULES:
            return "RULES";
        case TokenType::QUERIES:
            return "QUERIES";
        case TokenType::ID:
            return "ID";
        case TokenType::STRING:
            return "STRING";
        case TokenType::COMMENT:
            return "COMMENT";
        case TokenType::EOF_TYPE:
            return "EOF";
        default:
            return "UNDEFINED";

    }
}

Token::Token(TokenType type, std::string description, int line) {
    this->description = description;
    this->type = type;
    this->line = line;
    this->typeName = GetTypeName(type);
}

std::string Token::toString() {
    return "(" + typeName + ",\"" + description + "\"," + std::to_string(line) + ")";
}

TokenType Token::getTokenType() {
    return type;
}

string Token::getValue() {
    return description;
}