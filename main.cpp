/*
Author: Aakash Venkataraman
Class: ECE6122 A
Last Date Modified:  10/1/2022

Description:

Contains solveSudokuPuzzles() function which reads the sudoku grid,calls the solve and stores in output file
*/

#include <iostream>
#include <fstream>
#include <thread>         
#include <mutex>          
#include <string>
#include <cstdio>
#include "SudokuGrid.h"

using namespace std;

std::mutex inFileMutex; 
std::mutex outFileMutex; 

std::fstream inFile; 
std::fstream outFile; 

void solveSudokuPuzzles()
{//This function uses a do-while loop to keep reading through the input file till the EOF is reached
	SudokuGrid S; 
	int counter=0; 
	do
	{
        inFileMutex.lock(); 
        inFile>>S;
	    if(S.valid_input() == false)
		      counter=1;
	    inFileMutex.unlock(); 

	    if(counter == 1)
	        break;

	    S.solve(); 

	    outFileMutex.lock(); 
	    outFile<<S;
	    outFileMutex.unlock();
	}while(inFile.peek()!=EOF);
}

int main(int argc,char** argv)
{
    if(argc<2 || argc>3) //Checking number of arguments as per Lab1Problem 2
    {
        outFile.open("Lab2Prob2.txt",std::fstream::out);
        outFile<<"Invalid or Not sufficient Input arguments!";
        outFile.close();
        return 0;
    }

    if(argc == 2)
		{
        inFile.open(argv[1],std::fstream::in);
				outFile.open("Lab2Prob2.txt",std::fstream::out);
	  }
		else if(argc == 3)
		{
  			inFile.open(argv[1],std::fstream::in);
		    outFile.open(argv[2],std::fstream::out);
	  }
		

    unsigned int con_threads = std::thread::hardware_concurrency(); 
    std::thread threads[con_threads-1];

	for(int i=0;i<con_threads-1;i++)
        threads[i] = std::thread(solveSudokuPuzzles); //Calling threads to solve sudoku grid

    for (auto& th : threads)
    {
	    th.join(); //Wait till all threads complete their operations
    }

    inFile.close();
    outFile.close();
    return 0;
}
