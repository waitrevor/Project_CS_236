#include "Interpreter.h"
#include "Relation.h"
#include "Header.h"
#include "Tuple.h"
#include "Parser.h"


void Interpreter::SchemeToRelation() {
    vector<Predicate> schemes = datalogProgram.getSchemes();
    for (Predicate scheme: schemes) {
        string name = scheme.GetName();
        vector<Parameter> schemeParam = scheme.GetParameter();
        vector<string> att;
        for(unsigned int i = 0; i < schemeParam.size(); i++){
            att.push_back(schemeParam.at(i).toString());
        }
        Header h = Header(att);
        database.AddRelation(Relation(name, h));
    }
}

void Interpreter::FactToTuple() {
    vector<Predicate> facts = datalogProgram.getFacts();
    for (Predicate fact: facts){
        string name = fact.GetName();
        vector<Parameter> factParam = fact.GetParameter();
        Relation *r =  database.FindRelation(name);
        Tuple t = Tuple();
        for(unsigned int i = 0; i < factParam.size(); i++){
            t.SetValue(factParam.at(i).toString());
        }
        r->addTuple(t);
    }
}

Relation Interpreter::EvaluatePredicate(Relation* r, Predicate p) {
    vector<Parameter> param = p.GetParameter();
    vector<string> att;
    Relation rel = *r;
    variables.clear();
    vector <int> indicies;
    for(unsigned int i = 0; i < param.size(); i++){
        string currentParam = param.at(i).toString();
        if(param.at(i).isConst()) {
            rel = rel.select(i, param.at(i).toString());
            rel.SetConst(true);
            att.push_back(rel.GetAttribute(i));
        } else {
            map<string,int>::iterator it;
            it = variables.find(currentParam);
            att.push_back(currentParam);
            if(it != variables.end()) {
                rel = rel.select(variables.at(currentParam),i);
            } else {
                variables.insert(std::pair<string, int>(currentParam, i));
            }
            rel = rel.rename(att);
        }
    }
    return rel;
}

Relation Interpreter::EvaluateQueries(){
    vector<Predicate> queries = datalogProgram.getQueries();
    Relation *rel;
    Relation r;
    for(Predicate query : queries){
        string name = query.GetName();
        rel =  database.FindRelation(name);
        if(rel->GetName() != ""){
            r = EvaluatePredicate(rel, query);
            rel = &r;
            cout << QueryToString(query, rel);
        }
    }
    return r;
}

string Interpreter::QueryToString(Predicate p, Relation* r) {
    string output = "";
    vector<Parameter> param = p.GetParameter();
    output += p.toString() + "? ";
    if(!r->IsEmpty()){
        output += "Yes(" + to_string(r->Size()) + ")\n";
        output += r->toString(variables);
    } else {
        output += "No\n";
    }
    return output;
}