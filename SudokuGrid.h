/*
Author: Aakash Venkataraman
Class: ECE6122 A
Last Date Modified: 01/10/2022

Description:

Contains the class declaration of SudokuGrid class as mentioned in the Lab1 Problem 2 question
*/


#include <cstdio> 
#include <fstream>
#include <iostream>
#include <fstream>
#include <thread>         
#include <mutex>          
#include <string>

using namespace std;


class SudokuGrid
{
    public:

    std::string m_strGridName;
    unsigned char gridElement[9][9];

    bool isPresentInBox(int boxStartRow, int boxStartCol, int num); 
    bool findEmptyPlace(int &row, int &col); 
    bool isPresentInCol(int col, int num);
    bool isPresentInRow(int row, int num);
    bool isValidPlace(int row, int col, int num); 
    bool solve();
    bool valid_input(); 
    friend fstream& operator>>(fstream& os, SudokuGrid& gridIn); 
    friend fstream& operator<<(fstream& os, const SudokuGrid& gridIn); 
};
