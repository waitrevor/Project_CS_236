#ifndef PARAMETER_H
#define PARAMETER_H
#include "Token.h"

class Parameter{
private:
    bool isConstant;
    std::string value;
public:
    Parameter(){}
    Parameter(std::string t) {value = t; }
    bool isConst() { return isConstant;}
    void SetConstant(bool c){ isConstant = c; }
    std::string toString(){
        return value;
    }
};
#endif // PARAMETER_H