#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
using std::string;
#include <sstream>
#include <vector>
using std::vector;
#include <iostream>
using std::cout;

// this is provided code for the last part of the README k

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
  
private:
    std::string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};

// Do not edit above this line
// TODO: write code here:

double evaluateCountdown( string n){
string delimiter = " ";
n.append(" ");
size_t pos = 0;
string token;
vector <double> rpn;
while ((pos = n.find(delimiter)) != string::npos) {
    token = n.substr(0,pos);
    if (token.compare("+") == 0) {
        int x = rpn[1] + rpn[0];
        rpn.erase(rpn.begin(), rpn.begin()+2);
        rpn.insert(rpn.begin(), x);
    }
    if (token.compare("-") == 0){
        int x = rpn[1] - rpn[0];
        rpn.erase(rpn.begin(), rpn.begin()+2);
        rpn.insert(rpn.begin(), x);
    }
    if (token.compare("*") == 0){
        int x = rpn[1] * rpn[0];
        rpn.erase(rpn.begin(), rpn.begin()+2);
        rpn.insert(rpn.begin(), x);
    }
    if (token.compare("/") == 0){
        int x = rpn[1] / rpn[0];
        rpn.erase(rpn.begin(), rpn.begin()+2);
        rpn.insert(rpn.begin(), x);
    }
    if (token.find_first_of("0123456789") != string::npos) {
        rpn.insert(rpn.begin(), stod(token));
    }
    n.erase(0, pos + delimiter.length());
}
return rpn.front();
};

// Do not edit below this line


#endif
