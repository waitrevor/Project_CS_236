#ifndef TUPLE_H
#define TUPLE_H
#include <iostream>
#include <vector>

using namespace std;

class Tuple {

private:
   vector<string> values;
public:
   Tuple(){}
   ~Tuple(){}
   string GetValue(int n) {
       return values.at(n);
   }
   void SetValue(string value) {
       values.push_back(value);
   }
   int GetSize() {
       return values.size();
   }
   vector<string> GetTuple() {
       return values;
   }
   bool operator< (const Tuple &rhs) const {
       return values < rhs.values;
   }
};

#endif // TUPLE_H