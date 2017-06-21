#include <stdio.h>

typedef struct
{
    int rows;
    int cols;
    int *matrix;
} Puzzle;

int VALID_SUM;

//reads the sudoku puzzle in from a file passed as param
puzzle loadPuzzle(char *fileName)
{
    FILE file_ptr*;
}

//determines the size of the puzzle and a valid sum
int getSum(Puzzle puzzle)
{

}

//checks the row and return true or false 
int checkRow(Puzzle puzzle, int row)
{

}

//checks the colums and returns true or false if its valid
int checkCol(Puzzle puzzle, int col)
{

}

//checks the sector a 3x3 sub matrix to see if its valid
int checkSector(Puzzle puzzle, int sector)
{

}

int main(int argc, char *argv[])
{
}
