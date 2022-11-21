#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <iostream>
#include "Token.h"
#include <set>
#include "Predicate.h"
#include "Parameter.h"
#include "Datalog.h"

using namespace std;

class Parser {
private:
    vector<Token*> tokens;
    vector<string> schemes;
    vector<string> facts;
    vector<string> rules;
    vector<string> queries;
    set<string> domains;
    string tokenString;
    unsigned int itr;
    bool isFacts = false;
    bool notValid = false;
    Token* badToken;
    Datalog datalog = Datalog();
public:
    Parser(vector<Token *> tok);
    ~Parser();
    void removeComment();
    string toString();
    string badTokenString();
    void isValid();
    bool isValidToken();
    void ParseDatalog();
    void ParseColon();
    //void ParseSchemes();
    void ParseScheme();
    void ParseSchemeList();
    void ParseFacts();
    void ParseFact();
    void ParseFactList();
    void ParseRules();
    void ParseRule();
    void ParseRuleList();
    void ParseQueries();
    void ParseQuery();
    void ParseQueryList();
    void ParseEOF();
    void ParseLeft_Paren();
    void ParseRight_Paren();
    string ParseID();
    void ParseIDList(vector<Parameter>& param);
    void ParseColon_Dash();
    Predicate ParsePredicate();
    void ParsePredicateList(vector<Predicate>* pred);
    Predicate ParseHeadPredicate();
    void ParseComma();
    void ParsePeriod();
    void ParseQ_Mark();
    string ParseString();
    void ParseStringList(vector<Parameter>& param);
    Parameter ParseParameter();
    void ParseParameterList(vector<Parameter>& param);
    vector<string> GetSchemes();
    vector<string> GetFacts();
    vector<string> GetRules();
    vector<string> GetQueries();
    Datalog GetDatalog() {
        return datalog;
    }
};

#endif // PARSER_H