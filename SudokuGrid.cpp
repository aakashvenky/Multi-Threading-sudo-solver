/*
Author: Aakash Venkataraman
Class: ECE6122 A
Last Date Modified: 10/1/2022

Description:

Contains the definitions for the member functions of class SudokuGrid
*/

#include "SudokuGrid.h" 
#include <fstream>
#include <string.h>
#include <cstring>

using namespace std;


bool SudokuGrid::isPresentInCol(int col, int num)
{ //check whether num is present in col or not
    for (int row = 0; row < 9; row++)
        if (gridElement[row][col] == char(num+48))
            return true;
    return false;
}

bool SudokuGrid::isPresentInRow(int row, int num)
{ //check whether num is found in row or not found
    for (int col = 0; col < 9; col++)
        if (gridElement[row][col] == char(num+48))
            return true;
    return false;
}

bool SudokuGrid::isPresentInBox(int boxStartRow, int boxStartCol, int num)
{//check whether num is found in 3x3 box or not found
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (gridElement[row+boxStartRow][col+boxStartCol] == char(num+48))
                return true;
    return false;
}

bool SudokuGrid::findEmptyPlace(int &row, int &col)
{ //get empty location and update row and column
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (gridElement[row][col] == '0') 
                return true;
    return false;
}

bool SudokuGrid::isValidPlace(int row, int col, int num)
{//when item not found in col, row and current 3x3 box
    return !SudokuGrid::isPresentInRow(row, num) && !SudokuGrid::isPresentInCol(col, num) && !SudokuGrid::isPresentInBox(row - row%3 ,col - col%3, num);
}


bool SudokuGrid::solve()
{//Solve the input sudoku grid by finding the empty rows and columns
    int row, col;
    if (!SudokuGrid::findEmptyPlace(row, col))
        return true; //when all places are filled
    for (int num = 1; num <= 9; num++)
    { //valid numbers are 1 - 9
        if (SudokuGrid::isValidPlace(row, col, num))
        { //check validation, if yes, put the number in the grid
            gridElement[row][col] = char(num+48);
            if (solve()) //recursively go for other rooms in the grid
                return true;
            gridElement[row][col] = '0'; 
        }
    }
     return false;
}

bool SudokuGrid::valid_input()
{//Functions checks if the Input matrix is a valid matrix by checking line1 of the input which should contain the gridName
    if ((this->m_strGridName[0] != 'G') and (this->m_strGridName[1] != 'R'))
        return false;
    return true;
}

fstream& operator>>(fstream& os, SudokuGrid& gridIn)
{//Reads 1 matrix from the input file
    string line;
	for(int i=0;i<10;i++)
	{
	    getline(os,line);
	    if(i==0)
		{
			gridIn.m_strGridName = line;
		}
		else
		{
			for(int j=0;j<9;j++)
			    gridIn.gridElement[i-1][j] = line[j];
		}
	}
    return os;
}

fstream& operator<<(fstream& os, const SudokuGrid& gridIn)
{//Writes 1 matrix to the output file
 	os<<gridIn.m_strGridName<<"\n";
	for(int i=0;i<9;i++)
	{
        for (int j = 0; j < 9; j++)
        {
            os << gridIn.gridElement[i][j];
        }
	os<<"\n";
	}

    return os;
}
