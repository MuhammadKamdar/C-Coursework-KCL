#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

// Do not add any #include statements to this file

class SudokuSquareSet {

    // TODO: write your code here
    public:
    unsigned int values;
    int numberOfVal;

    SudokuSquareSet(){
        values = 0;
        numberOfVal = 0;
    }
    int size(){
        return numberOfVal;
    }
    bool empty(){
        if (values == 0){
            return true;
        }
        return false;
    }
    void clear(){
        values = 0;
    }


};


// Do not write any code below this line
static_assert(sizeof(SudokuSquareSet) == sizeof(unsigned int) + sizeof(int), "The SudokuSquareSet class needs to have exactly two 'int' member variables, and no others");


#endif
