#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int rows;
    int cols;
    int *matrix;
} Puzzle;

typedef enum
{
    row,
    sector,
    col
} type;

typedef struct
{
    type type;
    Puzzle Puzzle;
    int checkValue;
} parameters;

int VALID_SUM;

void printPuzzle(Puzzle puzzle)
{
    printf("read puzzle:\n");
    int i;
    for (i = 0; i < 9 * 9; i++)
    {
        if (i % 9 == 0 && i > 0) printf("\n");
        printf("%d ", *(puzzle.matrix + (i * sizeof(int))));
    }
    printf("\n");
}


//reads the sudoku puzzle in from a file passed as param
Puzzle loadPuzzle(char *fileName)
{
    printf("%s\n", fileName);
    FILE *file_ptr;
    file_ptr = fopen(fileName, "r");
    int temp, count = 0;

    Puzzle puzzle;
    puzzle.rows = 9;
    puzzle.cols = 9;
    puzzle.matrix = calloc(81, sizeof(int));

    while (fscanf(file_ptr, "%d", &temp) == 1 && count < 81)
    {
        *(puzzle.matrix + (count * sizeof(int))) = temp;
        printf("%d %d\n", temp, count);
        //temp = 0;
        count++;
    }

    printPuzzle(puzzle);
    return puzzle;
}

/*
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

void *enteryPoint(void* parameters)
{
    parameter *options = (parameter*) parameters;
    switch (options->type)
    {
        case row:
            break;
        case col:
            break;
        case sector:
            break;
    }
}
*/
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please provide the name of the file which contains the sudoku puzzle to check\n");
        printf("example usage: \"checker puzzle.txt\"\n");
        return 1;
    }

    Puzzle puzzle = loadPuzzle(argv[1]);
    return 1;
}
