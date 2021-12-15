/*
Implementation of board.h

Author: Daniel Townsend
*/

#include "board.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

Board::Board(int boardsize)
{
    this->boardSize = boardsize;
    board.resize(boardSize);
    for (int i = 0; i < boardSize; i++)
    {
        board.at(i).resize(boardSize);
    }
}

int Board::getBoardSize()
{
    return this->boardSize;
}

bool Board::hasQueenAtPos(int row, int col)
{
    return board.at(row).at(col) == "q";
}

void Board::putQueenAtPosition(int row, int col)
{
    board.at(row).at(col) = "q";
}

bool Board::isDiagonalSafe(int posRow, int posCol)
{
    int origRow = posRow;
    int origCol = posCol;

    // check right diagonal
    posRow--;
    while (posRow >= 0)
    {
        if (posCol < boardSize - 1)
        {
            if (board.at(posRow).at(posCol + 1) == "q")
            {
                return false;
            }
        }
        posRow--;
        posCol++;
    }

    // check left diagonal
    origRow--;
    while (origRow >= 0)
    {
        if (origCol > 0)
        {
            if (board.at(origRow).at(origCol - 1) == "q")
            {
                return false;
            }
        }
        origRow--;
        origCol--;
    }
    return true;
}

bool Board::IsColumnSafe(int row, int col)
{
    int currRow = row - 1;
    while (currRow >= 0)
    {
        if (board.at(currRow).at(col) == "q")
        {
            return false;
        }
        currRow--;
    }
    return true;
}

bool Board::isSafe(int row, int col)
{
    return (isDiagonalSafe(row, col) && IsColumnSafe(row, col));
}

void Board::resetQueenAtRow(int row)
{
    for (int col = 0; col < boardSize; col++)
    {
        if (board.at(row).at(col) == "q")
        {
            board.at(row).at(col) = "-";
        }
    }
}

// return the solution in printed format on ostream
ostream &operator<<(ostream &out, Board &b)
{
    for (int row = 0; row < b.boardSize; row++)
    {
        for (int col = 0; col < b.boardSize; col++)
        {
            if (b.board.at(row).at(col) == "q")
            {
                out << "Q";
            }
            else
            {
                out << "-";
            }
        }
        out << endl;
    }
    out << endl;
    return out;
}

// finds a single solution of given board
void Board::findASolution()
{
    cout << "A Solution of " << boardSize << "-Queen Problem " << endl
         << endl;
    Board b(boardSize);
    int row = 0;
    int col = 0;
    int prevCol = -1; // keeps track of the queen's column in previous row in order to backtrack

    while (row < b.boardSize)
    {
        while (col < b.boardSize)
        {
            if (b.isSafe(row, col))
            {
                b.putQueenAtPosition(row, col);
                if (row == b.boardSize - 1)
                {
                    cout << b;
                    return;
                }
                row++;
                col = 0;
                break;
            }
            col++;
        }

        // exhausted all column options
        if (col == b.boardSize)
        {
            row--;

            // determines what column we should start searching to the right of in row above in order
            // to backtrack
            for (int i = 0; i < boardSize; i++)
            {
                if (b.hasQueenAtPos(row, i))
                {
                    prevCol = i;
                    break;
                }
            }
            b.resetQueenAtRow(row);
            col = prevCol + 1;
        }
    }
}

void Board::findAllSolutions(bool isPrintToFile, int maxNumber)
{
    Board b(boardSize);
    int row = 0;
    int col = 0;
    int solutionsCount = 0;
    int prevCol = -1; // keeps track of the queen's column in previous row in order to backtrack

    ofstream outFS;
    outFS.open("solutions.txt");

    if (isPrintToFile)
    {
        outFS << boardSize << "-Queen Problem" << endl
              << endl;
    }
    else
    {
        cout << boardSize << "-Queen Problem" << endl
             << endl;
    }

    while (row < b.boardSize)
    {
        while (col < b.boardSize)
        {
            if (b.isSafe(row, col))
            {
                b.putQueenAtPosition(row, col);
                if (row == b.boardSize - 1)
                {
                    solutionsCount++;
                    if (solutionsCount <= maxNumber)
                    {
                        if (isPrintToFile)
                        {
                            outFS << "Solution:" << solutionsCount << endl;
                            outFS << b;
                        }
                        else
                        {
                            cout << "Solution:" << solutionsCount << endl;
                            cout << b;
                        }
                    }
                    b.resetQueenAtRow(row);
                    col++;
                    break;
                }
                row++;
                col = 0;
                break;
            }
            col++;
        }

        // exhausted all column options
        if (col >= b.boardSize)
        {

            // if we are at row 0 and cannot find a suitable column,
            // then we are done finding solutions
            if (row == 0)
            {
                break;
            }

            row--;

            // determines what column we should start searching to the right of in row above in order
            // to backtrack
            for (int i = 0; i < boardSize; i++)
            {
                if (b.hasQueenAtPos(row, i))
                {
                    prevCol = i;
                    break;
                }
            }
            b.resetQueenAtRow(row);
            col = prevCol + 1;
        }
    }
    cout << "Total number of solutions: " << solutionsCount << endl;
}
