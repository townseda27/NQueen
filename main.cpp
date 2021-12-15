/*
Finds either a single solution or all solutions to an
n x n board depending on user input via CLA. Makes use of an
iterative backtracking algorithm.

Author: Daniel Townsend
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include "board.h"
using namespace std;

int main(int argc, char *argv[])
{

    // if only 1 CLA is provided, then we tell the user that more arguments are needed
    if (argc == 1)
    {
        cout << "run with commandline parameters" << endl;
        cout << "boardsize, [-all] , {[-f]/[-c]:tofile or toconsole}, [numofsolutionToPrint]" << endl;
        return 0;
    }

    // make a new Board with user provided size
    Board myBoard(stoi(argv[1]));

    // perform desired action depending on CLA
    if (argc == 2)
    {
        myBoard.findASolution();
    }
    else if (argc == 3)
    {
        myBoard.findAllSolutions();
    }
    else if (argc == 4)
    {
        string arg = argv[3];
        if (arg == "-c")
        {
            myBoard.findAllSolutions(false, 3);
        }
        else
        {
            myBoard.findAllSolutions(true, 3);
        }
    }
    else if (argc == 5)
    {
        string arg = argv[3];
        if (arg == "-c")
        {
            myBoard.findAllSolutions(false, stoi(argv[4]));
        }
        else
        {
            myBoard.findAllSolutions(true, stoi(argv[4]));
        }
    }

    return 0;
}