#include "Relation.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

Relation Relation::select(int index, string value){
    Relation r = Relation(name, header); 
    for(Tuple t : rows) {
        if(t.GetValue(index) == value) { 
            r.addTuple(t); 
        }
    }
    return r; 
}

Relation Relation::select(int index1, int index2) {
    Relation r = Relation(name, header); 
    for(Tuple t : rows){ 
        if(t.GetValue(index1) == t.GetValue(index2)) {
            r.addTuple(t); 
        }
    }
    return r;
}

Relation Relation::project(vector<int> indices) {
    string newName = "";
    for(int index : indices) {
        newName += name.at(index);
    }
    Header h = Header();
    for(unsigned int i = 0; i < newName.size(); i++){
        string s(1, newName.at(i));
        h.AddAttribute(s);
    }
    Relation r = Relation(newName, h);
    for(Tuple t : rows) {
        Tuple tup = Tuple();
        for(int index : indices) {
            tup.SetValue(t.GetValue(index));
        }
        r.addTuple(tup);
    }
    return r;
}

Relation Relation::rename(vector<string> attributes) {
    Header h = header;
    for(unsigned int i = 0; i < attributes.size(); i++) {
        h.SetAttribute(i, attributes.at(i));
    }
    Relation r = Relation(name, h);
    r.SetTuples(rows);
    return r;
}

string Relation::toString(map<string, int> variables) {
    string output = "";
    string line;
    int itr = 0;
    for(Tuple t : rows) {
        output += "  ";
        for(int i = 0; i < t.GetSize(); i++) {
            if(parsedHeader.find(header.GetAttribute(i)) == parsedHeader.end()) {
                map<string, int>::iterator it = variables.find(header.GetAttribute(i));
                if (it != variables.end()) {
                    string equals = header.GetAttribute(i) + "=" + t.GetValue(i);
                    string check = output.substr(output.size() -2, output.size() -1);
                    if ((check.find(' ') == string::npos || output.find(line) == string::npos)) {
                        output += ", ";
                    }
                    if (line.find(equals) == string::npos) {
                        output += equals;
                        line = equals;
                    }
                }
                parsedHeader.insert(header.GetAttribute(i));
            }
        }
        if(itr < Size() && output != "  ") {
            output += "\n";
            line = "";
            parsedHeader.clear();
        }
        itr++;
    }
    if(output == "  ") {
        return "";
    }
    return output;
}