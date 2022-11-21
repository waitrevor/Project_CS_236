#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include "Relation.h"
#include "Header.h"
#include "Tuple.h"

using namespace std;

class Database{
private:
    map<string, Relation> relation;
public:
    Database(){}
    Database(string n){
        Relation r = Relation(n);
        relation.insert(pair<string, Relation>(n, r));
    }
    Relation* FindRelation(string n){
        if(relation.find(n) != relation.end()){
            return &relation.at(n);
        }
        return new Relation();
    }
    void AddRelation(Relation r){
        relation.insert(pair<string, Relation>(r.GetName(), r));
    }
    void RemoveRelation(string n){
        relation.erase(n);
    }
    void AddTuple(string n, Tuple t){
        relation.at(n).addTuple(t);
    }
    Relation GetRelation(string name){
        return relation.at(name);
    }
};

#endif // DATABASE_H