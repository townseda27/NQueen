/*
Header file for board.cpp

Author: Daniel Townsend
*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Board
{

private:
    int boardSize;
    vector<vector<string>> board;

public:
    Board(int boardsize = 4);
    int getBoardSize();                          // return the board size
    bool hasQueenAtPos(int row, int col);        // return true if there is a queen on the board[row][col]
    void putQueenAtPosition(int row, int col);   // put a queen on a specified position on the board
    bool isDiagonalSafe(int posRow, int posCol); // returns true if any queens can not attack diagonally on the board
    bool IsColumnSafe(int row, int col);         //returns true if no queens exist on the column col
    bool isSafe(int row, int col);               // return true if given position(row,col) is safe for diagonal and column attack
    void resetQueenAtRow(int row);               // erase the queen from the given row
    void findASolution();                        // print the first available solution to the console
    // find the all solutions and print maxNumber of solutions either on console or to "solutions.txt" file based on the isPrintFile value
    void findAllSolutions(bool isPrintToFile = false, int maxNumber = 3);
    friend ostream &operator<<(ostream &out, Board &b);
};

#endif
