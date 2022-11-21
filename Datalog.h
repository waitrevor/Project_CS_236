#ifndef DATALOG_H
#define DATALOG_H
#include "Parameter.h"
#include "Rule.h"
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Datalog {
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> queries;
    vector<Rule> rules;
    set<string> domain;
public:
    Datalog(){}
    ~Datalog(){}
    void addSchemes(Predicate s){
        schemes.push_back(s);
    }
    void addFacts(Predicate f){
        facts.push_back(f);
    }
    void addQueries(Predicate q){
        queries.push_back(q);
    }
    void addRules(Rule r){
        rules.push_back(r);
    }
    void setDatalog(set<string> d){
        domain = d;
    }
    vector<Predicate> getSchemes(){
        return schemes;
    }
    vector<Predicate> getFacts(){
        return facts;
    }
    vector<Predicate> getQueries(){
        return queries;
    }
};

#endif // DATALOG_H