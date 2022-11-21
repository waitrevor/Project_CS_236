#ifndef RULE_H
#define RULE_H
#include <iostream>
#include <vector>
#include "Predicate.h"

using namespace std;

class Rule{
private:
    Predicate head;
    vector<Predicate> body;
public:
    Rule(Predicate h, vector<Predicate> b) : head(h), body(b){}
    string toString(){
        string output = head.toString() + " :- ";
        for(unsigned int i = 0; i < body.size(); i++){
            output += body.at(i).toString();
            if(i != body.size()-1){
                output += ",";
            }
        }
        output += ".";
        return output;
    }

};

#endif // RULE_H