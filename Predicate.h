#ifndef PREDICATE_H
#define PREDICATE_H
#include <iostream>
#include "Parameter.h"
#include <vector>

class Predicate{
private:
    std::string name;
    std::vector<Parameter> parameter;
public:
    Predicate(std::string n, std::vector<Parameter> para){
        name = n;
        parameter = para;
    }
    std::string GetName() { return name; }
    std::vector<Parameter> GetParameter() { return parameter; }
    std::string toString(){
        std::string output = name + "(";
        for (unsigned int i = 0; i < parameter.size(); i++){
            output += parameter.at(i).toString();
            if(i != parameter.size()-1){
                output += ",";
            }
        }
        output += ")";
        return output;
    }

};

#endif // PREDICATE_H