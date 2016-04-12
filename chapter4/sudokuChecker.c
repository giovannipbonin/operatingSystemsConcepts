#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


typedef struct
{
    int row;
    int column;
    int thread;
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


static int sudoku[9][9];

int results[11];

void *subgridCheck(void *param)
{
    parameters *data = (parameters*) param;
    int i,j, threadNum;
    i = data->row; j = data->column; threadNum = data->thread;
    if (!checkSubgrid(sudoku, i, j))
    {
        results[threadNum] = 0;
        pthread_exit(0);
    }
    else
    {
        results[threadNum] = 1;
        pthread_exit(0);
    }
}

void *rowsCheck(void *param)
{
    int i;
    for (i=0; i < 9; i++)
    {
        if (!checkRow(sudoku, i))
        {
            results[0] = 0;
            pthread_exit(0);
        }
    }
    results[0] = 1;
    pthread_exit(0);
}


void *columnsCheck(void *param)
{
    int i;
    for (i=0; i < 9; i++)
    {
        if(!checkColumn(sudoku, i))
        {
            results[1] = 0;
            pthread_exit(0);
        }
    }
    results[1] = 1;
    pthread_exit(0);
}




int main()
{
    FILE *file = fopen("sudoku.txt", "r");
    int i, j;
    bool success;
    for (i=0; i < 9; i++)
    {
        for (j=0; j < 9; j++)
        {
            fscanf(file, "%d", &sudoku[i][j]);        
        }
    }
    fclose(file);
    pthread_t threads[11];
    int currentThread = 0;
    // Check columns
    pthread_create(&threads[currentThread], NULL, rowsCheck, NULL);
    currentThread++;
    // Check rows
    pthread_create(&threads[currentThread], NULL, columnsCheck, NULL);
    currentThread++;
    parameters *data[9];
    // Check subgrids
    for (i = 0; i < 9; i += 3)
    {
        for (j = 0; j < 9; j += 3)
        {
            data[currentThread - 2] = (parameters *) malloc(sizeof(parameters)); 
            data[currentThread - 2]->row = i; data[currentThread - 2]->column = j; data[currentThread - 2]->thread = currentThread;
            success = pthread_create(&threads[currentThread], NULL, subgridCheck, (void *) data[currentThread - 2]);
            if (success != 0)
            {
                fprintf(stderr, "Error creating thread");
                return -1;
            }
            currentThread++;
        }
    }
    for (i=0; i < 11; i++)
    {
        success = pthread_join(threads[i], NULL);
        if (success != 0)
        {
            fprintf(stderr, "Error joining thread");
            return -1;
        }
    }
    printf("Threads have been completed\n");
    for (currentThread=0; currentThread < 11; currentThread++)
    {
        if(results[currentThread] != 1)
        {
            printf("Invalid sudoku\n");
            exit(EXIT_SUCCESS);
        }
    }
    printf("Valid sudoku\n");
    exit(EXIT_SUCCESS);
}
