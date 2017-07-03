#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
    Puzzle puzzle;
    int checkValue;
    int tid;
    int result;
} Parameters;

#include <stdio.h>
#include <stdlib.h>

void printPuzzle(Puzzle puzzle)
{
    printf("read puzzle:\n");
    int i;
    for (i = 0; i < 9 * 9; i++)
    {
        if (i % 9 == 0 && i > 0) printf("\n");
        printf("%d ", *(puzzle.matrix + i));
    }
    printf("\n");
}


//reads the sudoku puzzle in from a file passed as param
Puzzle loadPuzzle(char *fileName)
{
    FILE *file_ptr;
    file_ptr = fopen(fileName, "r");
    int temp, count = 0;

    Puzzle puzzle;
    puzzle.rows = 9;
    puzzle.cols = 9;
    puzzle.matrix = calloc(81, sizeof(int));

    while (fscanf(file_ptr, "%d", &temp) == 1 && count < 81)
    {
        *(puzzle.matrix + count++) = temp;
    }

    printPuzzle(puzzle);
    return puzzle;
}

int checkRow(Puzzle puzzle, int row)
{
    int y;
    int *numberCheck = calloc(10, sizeof(int));
    for (y = 0; y < 9; y++)
    {
        if (*(puzzle.matrix + row * 9 + y) > 9)
        {
            free(numberCheck);
            return 0;
        }
        numberCheck[*(puzzle.matrix + row * 9 + y)]++;
    }
    if (numberCheck[0] != 0)
    {
        free(numberCheck);
        return 0;
    }
    for (y = 1; y < 10; y++)
    {
        //printf("%d\n ", numberCheck[y]);
        if (numberCheck[y] != 1)
        {
            free(numberCheck);
            return 0;
        }
    }
    free(numberCheck);
    return 1;
}
int checkCol(Puzzle puzzle, int col)
{
    int y;
    int *numberCheck = calloc(10, sizeof(int));
    for (y = 0; y < 9; y++)
    {
        if ( *(puzzle.matrix + col + 9 * y) > 9)
        {
            free(numberCheck);
            return 0;
        }
        numberCheck[*(puzzle.matrix + col + 9 * y)]++;
    }
    if (numberCheck[0] != 0)
    {
        free(numberCheck);
        return 0;
    }
    for (y = 1; y < 10; y++)
    {
        if (numberCheck[y] != 1)
        {
            free(numberCheck);
            return 0;
        }
    }
    free(numberCheck);
    return 1;
}


int checkSector(Puzzle puzzle, int sector)
{
    //x = start of the block
    //x needs to hit, 0, 3, 6, 27, 30, 33, 54, 57, 60
    int x, z, n;
    int *numberCheck = calloc(10, sizeof(int));
    //sector--;
    if (sector < 3) x = sector * 3;
    else if (sector < 6) x = 27 + sector * 3;
    else if (sector < 9) x = 54 + sector * 3;
    else
    {
        printf("something went wrong\n");
        exit(0);
    }

    for (z = 0; z < 27; z += 9)
    {
        for (n  = 0; n < 3; n++)
        {
            if (*(puzzle.matrix + x + z + n) > 9)
            {
                free(numberCheck);
                return 0;
            }
            numberCheck[*(puzzle.matrix + x + z + n)]++;
            //total += *(puzzle.matrix + x + z + n);
        }
    }
    if (numberCheck[0] != 0)
    {
        free(numberCheck);
        return 0;
    }
    for (x = 1; x < 10; x++)
    {
        if (numberCheck[x] != 1)
        {
            free(numberCheck);
            return 0;
        }
    }
    free(numberCheck);
    return 1;
}

void *entryPoint(void* parameter)
{
    Parameters * options = (Parameters*)parameter;
    switch (options->type)
    {
        case row:
            options->result = checkRow(options->puzzle, options->checkValue);
            break;
        case col:
            options->result = checkCol(options->puzzle, options->checkValue);
            break;
        case sector:
            options->result = checkSector(options->puzzle, options->checkValue);
            break;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int x, y = 0, r;
    int *results = calloc(27, sizeof(int));
    Parameters **t_args = calloc(27, sizeof(Parameters*));
    if (argc < 2)
    {
        printf("Please provide the name of the file which contains the sudoku puzzle to check\n");
        printf("example usage: \"checker puzzle.txt\"\n");
        return 1;
    }

    pthread_t tid[27];

    Puzzle puzzle = loadPuzzle(argv[1]);

    for (x = 0; x < 9; x++)
    {
        Parameters *args = calloc(1, sizeof(Parameters));
        args->type = row;
        args->checkValue = x;
        args->puzzle = puzzle;
        args->tid = y;

        t_args[y] = args;

        r = pthread_create(&tid[y], NULL, entryPoint, args);
        y++;
    }
    for (x = 0; x < 9; x++)
    {
        Parameters *args = calloc(1, sizeof(Parameters));
        args->type = sector;
        args->checkValue = x;
        args->puzzle = puzzle;
        args->tid = y;

        t_args[y] = args;

        r = pthread_create(&tid[y], NULL, entryPoint, args);
        y++;
    }
    for (x = 0; x < 9; x++)
    {
        Parameters *args = calloc(1, sizeof(Parameters));
        args->type = col;
        args->checkValue = x;
        args->puzzle = puzzle;
        args->tid = y;

        t_args[y] = args;

        r = pthread_create(&tid[y], NULL, entryPoint, args);
        y++;
    }

    for (x = 0; x < 27; x++)
    {
        pthread_join(tid[x], NULL);
        results[x] = t_args[x]->result;
    }

    for (x = 0; x < 27; x++)
    {
        printf("%d\n", results[x]);
        if (results[x] != 1)
        {
            printf("Not a valid Sudoku solution\n");
            return 1;
        }
    }
    /*
    for (x = 0; x < 9; x++)
    {
        int temp = checkSector(puzzle, x);
        printf("%d\n", temp);
    }
    */
    printf("The solution is valid!\n");
    return 1;
}