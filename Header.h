#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <vector>

using namespace std;
class Header{
private:
    vector<string> attributes;
public:
    Header(){}
    ~Header(){}
    Header (vector<string> att){
        attributes = att;
    }
    string GetAttribute(int n){
        return attributes.at(n);
    }
    string GetFirstAttribute(){
        return attributes.at(0);
    }
    void AddAttribute(string att){
        attributes.push_back(att);
    }
    int FindAttribute(string att){
        for(unsigned int i = 0; i < attributes.size(); i++){
            if(attributes.at(i) == att){
                return i;
            }
        }
        return -1;
    }
    void SetAttribute(int n, string att){
        attributes.at(n) = att;
    }
};

#endif // HEADER_H