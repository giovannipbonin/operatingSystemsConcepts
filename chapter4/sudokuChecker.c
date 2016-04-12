#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


typedef struct
{
    int row;
    int column;
} parameters;



bool checkRow(int arr[9][9], int row)
{
    int bitmap = 0;
    int i;
    for (i=0; i < 9; i++)
    {
        bitmap = bitmap | (int)pow(2, arr[row][i] - 1);
    }
    if (bitmap == 511) return true;
    return false;
}

bool checkColumn(int arr[9][9], int col)
{
    int bitmap = 0;
    int i;
    for (i=0; i < 9; i++)
    {
        bitmap = bitmap | (int)pow(2, arr[i][col] - 1);
    }
    if (bitmap == 511) return true;
    return false;
}

bool checkSubgrid(int arr[9][9], int row, int col)
{
    int bitmap = 0;
    int i, j;
    for (i = row; i < row + 3; i++)
    {
        for (j = col; j < col + 3; j++)
        {
            bitmap = bitmap | (int)pow(2, arr[i][j] - 1);
        }
    }
    if (bitmap == 511) return true;
    return false;
}


int sudoku[9][9] = {{1,2,3,4,5,6,7,8,9},{4,5,6,1,2,3,7,8,9},{7,8,9,7,8,9,7,8,9}, {1,2,3,4,5,9,7,8,9},{1,2,3,4,5,1,7,8,9},{1,2,3,4,5,2,7,8,9},{1,2,3,4,5,3,7,8,9},{1,2,3,4,5,4,7,8,9},{1,2,3,4,5,5,7,8,9}};







int results[11];

void *rowsCheck(void *param)
{
    int i;
    for (i=0; i < 9; i++)
    {
        if (!checkRow(sudoku, i));
        {
            results[0] = 0;
            return NULL;
        }
    }
}

void *columnsCheck(void *param)
{
    int i;
    for (i=0; i < 9; i++)
    {
        if(!checkRow(sudoku, i))
        {
            results[1] = 0;
            return NULL;
        }
    }
}




int main()
{
    /*
    pthread_t threads[11];
    int currentThread = 0;
    // Check columns
    pthread_create(&threads[currentThread], NULL, rowsCheck, NULL);
    currentThread++;
    // Check rows
    pthread_create(&threads[currentThread], NULL, columnsCheck, NULL);
    currentThread++;
    // Check subgrids
    int i, j;
    for (i = 0; i < 9; i += 3)
    {
        for (j = 0; j < 9; j += 3)
        {
            parameters *data = (parameters *) malloc(sizeof(parameters)); 
            data->row = i; data->column = j;
            pthread_create(&threads[currentThread], NULL, subgridCheck, (void *) data);
            currentThread++;
        }
    }
    */
    printf("row: %d", checkRow(sudoku, 1));
    printf("col: %d", checkColumn(sudoku, 5));
    printf("grid: %d", checkSubgrid(sudoku, 0, 3));

}
