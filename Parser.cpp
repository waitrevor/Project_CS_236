#include "Parser.h"
#include <iostream>
#include <algorithm>
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

Parser::Parser(vector <Token *> tok) {
    tokens = tok;
    itr = 0;
}

Parser::~Parser() {
}

void Parser::removeComment() {
    Token* currentToken = tokens.at(itr);
    while (currentToken->getTokenType() == TokenType::COMMENT && itr < tokens.size()){
        itr++;
        currentToken = tokens.at(itr);
    }
}

void Parser::isValid() {
    notValid = true;
    badToken = tokens.at(itr);
}

bool Parser::isValidToken(){
    return notValid;
}

string Parser::badTokenString() {
    return badToken->toString();
}

void Parser::ParseDatalog() {
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::SCHEMES){
        itr++;
        ParseColon();
        ParseScheme();
        ParseSchemeList();
        ParseFacts();
        ParseColon();
        ParseFactList();
        isFacts = false;
        ParseRules();
        ParseColon();
        ParseRuleList();
        ParseQueries();
        ParseColon();
        ParseQuery();
        ParseQueryList();
        ParseEOF();
        datalog.setDatalog(domains);
    } else {
        isValid();
    }
}

string Parser::toString(){
    string output;
    cout << "Schemes(" << schemes.size() << "):" << endl;
    for(unsigned int i = 0; i < schemes.size(); i++){
        cout << "  " << schemes.at(i) << endl;
    }
    cout << "Facts(" << facts.size() << "):" << endl;
    for(unsigned int i = 0; i < facts.size(); i++){
        cout << "  " << facts.at(i) << endl;
    }
    cout << "Rules(" << rules.size() << "):" << endl;
    for(unsigned int i = 0; i < rules.size(); i++){
        cout << "  " << rules.at(i) << endl;
    }
    cout << "Queries(" << queries.size() << "):" << endl;
    for(unsigned int i = 0; i < queries.size(); i++){
        cout << "  " << queries.at(i) << endl;
    }
    set<string>:: iterator it;
    cout << "Domain(" << domains.size() << "):" << endl;
    for(it = domains.begin(); it != domains.end(); it++){
        string domain = *it;
        cout << "  " << domain << endl;
    }
    return output;
}

void Parser::ParseColon(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::COLON && !notValid){
        itr++;
        return;
    } else {
        isValid();
    }
}

void Parser::ParseLeft_Paren() {
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::LEFT_PAREN && !notValid){
        tokenString += currentToken->getValue();
        itr++;
        return;
    } else {
        isValid();
    }
}

void Parser::ParseRight_Paren(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::RIGHT_PAREN && !notValid){
        tokenString += currentToken->getValue();
        itr++;
        return;
    } else {
        isValid();
    }
}

void Parser::ParsePeriod(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::PERIOD && !notValid){
        tokenString += currentToken->getValue();
        itr++;
    } else {
        isValid();
    }
}

void Parser::ParseColon_Dash(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::COLON_DASH && !notValid){
        tokenString += " " + currentToken->getValue() + " ";
        itr++;
    } else {
        isValid();
    }
}

void Parser::ParseQ_Mark(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::Q_MARK && !notValid){
        tokenString += currentToken->getValue();
        itr++;
    } else {
        isValid();
    }
}

void Parser::ParseComma(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::COMMA && !notValid){
        tokenString += currentToken->getValue();
        itr++;
    } else {
        isValid();
    }
}

void Parser::ParseEOF(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::EOF_TYPE && !notValid){
        itr++;
    } else {
        isValid();
    }
}

void Parser::ParseScheme(){

    vector<Parameter> param;
    removeComment();
    string n = ParseID();
    ParseLeft_Paren();
    string str = ParseID();
    param.push_back(Parameter(str));
    ParseIDList(param);
    ParseRight_Paren();
    Predicate scheme = Predicate(n, param);
    datalog.addSchemes(scheme);
    schemes.push_back(tokenString);
    tokenString = "";
}

void Parser::ParseSchemeList(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() != TokenType::FACTS && !notValid){
        removeComment();
        ParseScheme();
        ParseSchemeList();
    }
}

void Parser::ParseFacts() {
    removeComment();
    Token *currentToken = tokens.at(itr);
    if (currentToken->getTokenType() == TokenType::FACTS && !notValid) {
        isFacts = true;
        itr++;
    } else {
        isValid();
    }
}

void Parser::ParseFact() {
    vector<Parameter> param;
    removeComment();
    string n = ParseID();
    ParseLeft_Paren();
    param.push_back(ParseString());
    ParseStringList(param);
    ParseRight_Paren();
    ParsePeriod();
    datalog.addFacts(Predicate(n, param));
    facts.push_back(tokenString);
    tokenString = "";
}

void Parser::ParseFactList(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() != TokenType::RULES && !notValid){
        removeComment();
        ParseFact();
        ParseFactList();
    }
}

void Parser::ParseRules(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::RULES && !notValid){
        itr++;
    } else {
        isValid();
    }
}

void Parser::ParseRule(){
    vector<Predicate> pred;
    removeComment();
    Predicate head = ParseHeadPredicate();
    ParseColon_Dash();
    pred.push_back(ParsePredicate());
    ParsePredicateList(&pred);
    ParsePeriod();
    Rule rule = Rule(head, pred);
    datalog.addRules(rule);
    rules.push_back(tokenString);
    tokenString = "";
}

void Parser::ParseRuleList(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() != TokenType::QUERIES && !notValid){
        removeComment();
        ParseRule();
        ParseRuleList();
    }
}

void Parser::ParseQueries(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::QUERIES && !notValid){
        itr++;
    } else {
        isValid();
    }
}

void Parser::ParseQuery(){
    removeComment();
    datalog.addQueries(ParsePredicate());
    ParseQ_Mark();
    queries.push_back(tokenString);
    tokenString = "";
}

void Parser::ParseQueryList(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() != TokenType::EOF_TYPE && !notValid){
        removeComment();
        ParseQuery();
        ParseQueryList();
    }
}

string Parser::ParseID(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::ID && !notValid){
        string str = currentToken->getValue();
        tokenString += str;
        itr++;
        return str;
    } else {
        isValid();
    }
    return "";
}

void Parser::ParseIDList(vector<Parameter>& param){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() != TokenType::RIGHT_PAREN && !notValid){
        ParseComma();
        string str = ParseID();
        param.push_back(Parameter(str));
        ParseIDList(param);
    }
}

void Parser::ParseStringList(vector<Parameter>& param){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() != TokenType::RIGHT_PAREN && !notValid){
        ParseComma();
        param.push_back(ParseString());
        ParseStringList(param);
    }
}

Predicate Parser::ParseHeadPredicate() {
    vector<Parameter> param;
    removeComment();
    string n = ParseID();
    ParseLeft_Paren();
    string str = ParseID();
    param.push_back(Parameter(str));
    ParseIDList(param);
    ParseRight_Paren();
    return Predicate (n, param);
}

Predicate Parser::ParsePredicate(){
    vector<Parameter> param;
    removeComment();
    string n = ParseID();
    ParseLeft_Paren();
    param.push_back(ParseParameter());
    ParseParameterList(param);
    ParseRight_Paren();
    return Predicate(n, param);
}

void Parser::ParsePredicateList(vector<Predicate>* pred){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() != TokenType::PERIOD && !notValid){
        ParseComma();
        pred->push_back(ParsePredicate());
        ParsePredicateList(pred);
    }
}

Parameter Parser::ParseParameter(){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::STRING && !notValid){
        Parameter p = Parameter(ParseString());
        p.SetConstant(true);
        return p;
    } else if (currentToken->getTokenType() == TokenType::ID && !notValid){
        Parameter p = Parameter(ParseID());
        p.SetConstant(false);
        return p;
    } else {
        isValid();
    }
    return Parameter("");
}

void Parser::ParseParameterList(vector<Parameter>& param){
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() != TokenType::RIGHT_PAREN && !notValid){
        ParseComma();
        param.push_back(ParseParameter());
        ParseParameterList(param);
    }
}

string Parser::ParseString() {
    removeComment();
    Token* currentToken = tokens.at(itr);
    if(currentToken->getTokenType() == TokenType::STRING && !notValid){
        tokenString += currentToken->getValue();
        if(isFacts){
            domains.insert(currentToken->getValue());
        }
        itr++;
        return currentToken->getValue();
    } else {
        isValid();
    }
    return "";
}