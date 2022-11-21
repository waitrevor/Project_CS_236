#ifndef AUTOMATON_H
#define AUTOMATON_H
#include "Token.h"

class Automaton
{
protected:
    int inputRead = 0;
    int newLines = 0;
    int unsigned index = 0;
    TokenType type;

public:
    // Default constructor -- since we have a constructor that takes a parameter,
    //   the compiler will autogenerate a default constructor if not explicit.
    Automaton() : Automaton(TokenType::UNDEFINED) {}

    Automaton(TokenType type) { this->type = type; }

    virtual ~Automaton() = default;

    // Start the automaton and return the number of characters read
    //   read == 0 indicates the input was rejected
    //   read  > 0 indicates the input was accepted
    int Start(const std::string& input) {
        newLines = 0;
        inputRead = 0;
        index = 0;
        S0(input);
        return inputRead;
    }

    // Every subclass must define this method
    virtual void S0(const std::string& input) = 0;

    void Serr() {
        // Indicate the input was rejected
        inputRead = 0;
    }

    virtual Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }

    int NewLinesRead() const { 
        return newLines;
    }
};

class AddAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    AddAutomaton() : Automaton(TokenType::ADD) {}  // Call the base constructor

};

class ColonAutomaton : public Automaton
{
public:
    ColonAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

class ColonDashAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    ColonDashAutomaton() : Automaton(TokenType::COLON_DASH) {}  // Call the base constructor

    void S0(const std::string& input);
};

class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}  // Call the base constructor

    void S0(const std::string& input);
};

class CommentAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor
};

class EOFAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    EOFAutomaton() : Automaton(TokenType::EOF_TYPE) {}  // Call the base constructor
};

class FactsAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    FactsAutomaton() : Automaton(TokenType::FACTS) {}  // Call the base constructor
};

class IDAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    IDAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor
};

class LeftParenAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    LeftParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}
};

class MultiplyAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

};

class PeriodAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

};

class QMarkAutomaton : public Automaton
{
public:
    void S0(const std::string& input);

    QMarkAutomaton() : Automaton(TokenType::Q_MARK) {}
};

class QueriesAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    QueriesAutomaton() : Automaton(TokenType::QUERIES) {}  // Call the base constructor
};

class RightParenAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

};

class RulesAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    RulesAutomaton() : Automaton(TokenType::RULES) {}  // Call the base constructor
};

class SchemesAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    SchemesAutomaton() : Automaton(TokenType::SCHEMES) {}  // Call the base constructor
};

class StringAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor
};

class UndefinedAutomaton : public Automaton
{
public:
    void S0(const std::string& input);
    UndefinedAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor
};
#endif // AUTOMATON_H