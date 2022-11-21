#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "Parser.h"
#include "Database.h"
#include <map>

class Interpreter{
private:
    Datalog datalogProgram;
    Database database;
    map <std::string, int> variables;
public:
    Interpreter(Datalog d){
       datalogProgram = d;
    };
    void SchemeToRelation();
    void FactToTuple();
    Relation EvaluatePredicate(Relation* r, Predicate p);
    Relation EvaluateQueries();
    string QueryToString(Predicate p, Relation* r);
};


#endif // INTERPRETER_H