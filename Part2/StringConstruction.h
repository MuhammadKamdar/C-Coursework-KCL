#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;


// TODO: your code goes here:

int stringConstruction(string target, int cloneCost, int appendCost){
    string myString = "";
    int totalCost;
    int size = target.length();
    int* costs = new int[size];
    costs[0] = appendCost;
    //initial cost for letter 1
    for (int i = 1; i<size; i++){
        myString += target.at(i);
        while (myString.length()>0){
            if (target.substr(0, i+1-myString.length()).find(myString) != std::string::npos){
                break;
            }
            myString = myString.substr(1, myString.size());
        }
        if (myString.length() > 0){
            if ((costs[i-1]+appendCost) > (costs[i-myString.length()]+cloneCost)){
                costs[i] = costs[i-myString.length()] + cloneCost;
            }
            else {
                costs[i] = costs[i-1]+appendCost;
            }
        }
        else{
            costs[i] = costs[i-1]+appendCost;
        }
    }
    totalCost = costs[size-1];
    //delete the array
    delete [] costs;
    return totalCost;
}



// do not write or edit anything below this line

#endif
