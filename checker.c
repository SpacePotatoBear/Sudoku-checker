#include <stdio.h>

typedef struct
{
    int rows;
    int cols;
    int *matrix;
} Puzzle;

int VALID_SUM;

//reads the sudoku puzzle in from a file passed as param
Puzzle loadPuzzle(char *fileName)
{
    FILE *file_ptr;
}

//determines the size of the puzzle and a valid sum
int getSum(Puzzle puzzle)
{
    int x, total = 0;
    for (x = 1; x <= 9; x++) total += x;
    return x;
}

int checkRow(Puzzle puzzle, int row)
{
    int y, total = 0;
    for (y = 0; y < 9; y++)
    {
        total += *(puzzle.matrix + row * 9 + y);
    }
    return (total == VALID_SUM) ? 0 : 1;
}

int checkCol(Puzzle puzzle, int col)
{
    int y, total = 0;
    for (y = 0; y < 9; y++)
    {
        total += *(puzzle.matrix + col + y * 9);
    }
    return (total == VALID_SUM) ? 0 : 1;
}


int checkSector(Puzzle puzzle, int sector)
{
    //x = start of the block
    //x needs to hit, 0, 3, 6, 27, 30, 33, 54, 57, 60
    int x, z, n, total;

    sector--;
    if (sector < 3) x = sector * 3;
    else if (sector < 6) x = 27 + sector * 3;
    else if (sector < 9) x = 54 + sector * 3;
    else
    {
        printf("something went wrong\n");
        exit(0);
    }

    total = 0;
    for (z = 0; z < 27; z += 9)
    {
        for (n  = 0; n < 3; n++)
        {
            total += *(puzzle.matrix + x + z + n);
        }
    }
    return (total == VALID_SUM) ? 0 : 1;
}

int main(int argc, char *argv[])
{
}
