#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <vector>
using std::vector;
#include <set>
using std::set;
#include <iterator>
using std::iterator;
#include <math.h>
using std::sqrt;
#include <ostream>
using std::cout;
#include <string>
using std::string;

// TODO: Your Sudoku class goes here:
class Sudoku : public Searchable{
    public:
    const int size;
    vector<vector<set<int>>> board;
    
    Sudoku(int boardSize)
        : size(boardSize){
            board.resize(size, vector<set<int>>(size));

            for (int i = 0; i < size; i++){
                for (int j = 0; j < size ; j++){
                    board[i][j].insert(1);
                    board[i][j].insert(2);
                    board[i][j].insert(3);
                    board[i][j].insert(4);
                    board[i][j].insert(5);
                    board[i][j].insert(6);
                    board[i][j].insert(7);
                    board[i][j].insert(8);
                    board[i][j].insert(9);
                }
            }
        }
        Sudoku(const Sudoku& other)
        : size(other.size){
            board.resize(size, vector<set<int>>(size));
            for (int row = 0; row < size; row++){
                for(int col = 0; col<size; col++){
                    for (auto& value: other.board[row][col]){
                        board[row][col].insert(value);
                    }
                }
            }

        }
            int getSquare(int row, int col){
                if (board[row][col].size() == 1){
                    auto it = board[row][col].begin();
                    return *it;
                }
                else {
                    return -1;
                }

            }

            bool setSquare(int row, int col, int value){
                board[row][col].clear();
                board[row][col].insert(value);
                
                for (int i = 0; i < size; i++){
                    for (int j = 0; j<size; j++){
                        if (board[i][j].empty()){
                            return false;
                        }
                        else if (board[i][j].size() == 1){
                            for (int m = 0; m < size; m++){
                                if (board[i][m].size()>1){
                                    board[i][m].erase(*board[i][j].begin());
                                    //cout << *board[i][j].begin() << " erased\n";
                                    runParallelCheck(i,m);
                                }
                            }
                            for (int n = 0; n < size; n++){
                                if (board[n][j].size()>1){
                                    board[n][j].erase(*board[i][j].begin());
                                    runParallelCheck(n,j);
                                }
                            }
                            int rootSize = sqrt(board.size());
                            int tempRow = i%rootSize;
                            tempRow = i - tempRow;

                            int tempCol = j % rootSize;
                            tempCol = j - tempCol;

                            int rowUpper = tempRow + rootSize;
                            int colUpper = tempCol + rootSize;

                            for (int p =tempRow; p < rowUpper; p++){
                                for (int q = tempCol; q<colUpper; q++){
                                    if (board[p][q].size()>1){
                                        board[p][q].erase(*board[i][j].begin());
                                        runParallelCheck(p, q);
                                    }
                                }
                            }
                        }
                    }
                }
                //write(cout);
                return true;
            }

            void runParallelCheck(const int row, const int col){
                if (getSquare(row,col) != -1){
                    for (int i = 0; i < size; i++){
                        if (board[row][i].size() > 1){
                            /**if (!removeDebug(row,i,*board[row][col].begin())){
                                cout << "error in runParallel check when removing value from row\n";
                                }*/
                            board[row][i].erase(*board[row][col].begin());
                            runParallelCheck(row,i);
                        }
                    }
                    for (int j = 0; j <size; j++){
                        if (board[j][col].size() > 1){
                            /**if (!removeDebug(j,col,*board[row][col].begin())){
                                cout << "error in runParallel check when removing value from column\n";
                                }*/
                            board[j][col].erase(*board[row][col].begin());
                            runParallelCheck(j,col);
                        }
                    }
                    int rootSize = sqrt(size);
                    int tempRow = row%rootSize;
                    tempRow = row - tempRow;

                    int tempCol = col % rootSize;
                    tempCol = col - tempCol;

                    int rowUpper = tempRow + rootSize;
                    int colUpper = tempCol + rootSize;

                    for (int p = tempRow; p < rowUpper; ++p){
                        for (int q = tempCol; q < colUpper; ++q){
                            if (board[p][q].size()>1){
                                board[p][q].erase(*board[row][col].begin());
                                runParallelCheck(p,q);
                            }
                            
                        }
                    }
                }
            }

            virtual bool isSolution()const {
                for (int i = 0; i<board.size(); i++){
                    for (int j = 0; j<board.size(); j++){
                        if (board[i][j].size() > 1){
                            return false;
                        }
                    }
                }
                return true;
            }
            /**
            virtual vector<unique_ptr<Searchable> > successors()const //override
            {
                int numberSuc = 0;
                vector<unique_ptr<Searchable>> successors;
                int foundRow;
                set<int> leftSquare;
                for (int i = 0; i<size; i++){
                    for (int j = 0; j<size; j++){
                        if (board[i][j].size() > 1){
                            for (auto & value: board[i][j]){
                                Sudoku *copySudoku = new Sudoku(*this);
                                if (copySudoku->setSquare(i, j, value)){
                                    successors.emplace_back(copySudoku);
                                }
                                else
                                {
                                    delete copySudoku;
                                }
                            }
                            //return successors;
                        }
                    }
                }
                return successors;
            }*/
            virtual int heuristicValue() const {
                int heuristic = 0;
                 for (int i = 0; i<board.size(); i++){
                    for (int j = 0; j<board.size(); j++){
                        if (board[i][j].size() > 1){
                            heuristic++;
                        }
                    }
                }
                return heuristic;
            }
            bool removeDebug(int row, int col, int value){
                vector<string> answer{  "812753649",
                                "943682175",
                                "675491283",
                                "154237896",
                                "369845721",
                                "287169534",
                                "521974368",
                                "438526917",
                                "796318452"};
                    const int setTo = std::stoi(answer[row].substr(col,1));
                    if (value == setTo) {
                    cout << "Error: " << value << " should not be removed from [" << row << "][" << col << "]\n";
                    return false;
                }
                else {return true;}
            }
            
            virtual vector<unique_ptr<Searchable>> successors() const{
                int foundRow;
                int foundCol;
                bool forBreak = false;
                int numberSuc = 0;
                vector<unique_ptr<Searchable>> successors;
                for (int i = 0; i<size; i++){
                    for (int j = 0; j<size; j++){
                        if (board[i][j].size() > 1){
                            foundRow = i;
                            foundCol = j;
                            forBreak= true;
                            break;
                        }
                    }
                    if (forBreak){break;}
                }
                for (auto & value: board[foundRow][foundCol]){
                    Sudoku *copySudoku = new Sudoku(*this);
            /**
                        numberSuc++;
                        cout << "Successor number: "<< numberSuc << "\n";*/
                    if (copySudoku->setSquare(foundRow, foundCol, value)){
                        successors.emplace_back(copySudoku);
                    }
                    else
                    {
                        delete copySudoku;
                    }
                }
                return successors;

            }
            virtual void write(ostream & o) const{
                for (int i = 0; i < size; i++){
                    o << "|";
                    for (int j = 0; j<size; j++){
                        //for (auto & m: board[i][j]){
                            if (board[i][j].size() == 1){
                                o<< *board[i][j].begin();
                            }
                            else {
                                o << " ";
                            }
                    o << "|";
                    }
                    o << "\n";
                }
            }
            /**
            void printSolution(){
                for (int i = 0; i < size; i++){
                    for (int j = 0; j<size; j++){
                        cout << "{";
                        for (auto & m: board[i][j]){
                        cout << m << " ";
                        
                    }
                    cout << "}";
                    }
                    cout << "\n";
                }
            }*/

            void checkRemoved(int row, int col, int value) const{
                for (int i = 0; i < size; i++){
                        if (board[row][i].size() > 1){
                            set<int>::iterator iter = board[row][i].find(value);
                            if (iter != board[row][i].end()){
                                cout<< value << " has not been removed from square "<< row<< " "<< i<< "\n";
                                cout << "row error\n";
                            }
                        }
                    }
                    for (int j = 0; j <size; j++){
                        if (board[j][col].size() > 1){
                            set<int>::iterator iter = board[j][col].find(value);
                            if (iter != board[j][col].end()){
                                cout<< value << " has not been removed from square "<< j<< " "<< col<< "\n";
                                cout << "col error\n";
                            }
                        }
                    }
                            int rootSize = sqrt(size);
                            int tempRow = row%rootSize;
                            tempRow = row - tempRow;

                            int tempCol = col%rootSize;
                            tempCol = col - tempCol;

                            int rowUpper = tempRow + rootSize;
                            int colUpper = tempCol + rootSize;

                            for (tempRow; tempRow<rowUpper; ++tempRow){
                                for (tempCol; tempCol<colUpper; ++tempCol){
                                    if (board[tempRow][tempCol].size()>1){
                                        set<int>::iterator iter = board[tempRow][tempCol].find(value);
                                        if (iter != board[tempRow][tempCol].end()){
                                            cout<< value << " has not been removed from square "<< tempRow<< " "<< tempCol<< "\n";
                                            cout << "box error\n";
                                        }
                                    }
                                }
                            }

            }



    };



#endif
