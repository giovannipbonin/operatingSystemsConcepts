#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define ARRAY_SIZE 100 // For simplicity this program assumes the number is even

int unsortedArray[ARRAY_SIZE];
int sortedArray[ARRAY_SIZE];

void sort(int *unsorted, int *sorted, int size);
void merge(int *arr1, int size1, int *arr2, int size2, int *merged);
int cmpfunc(const void *a, const void *b);
void *mergeWorker(void *param);
void *qsortWorker(void *param);

typedef struct
{
    int start1, start2;

} arraysContainer;

int main()
{
    // Initialize array
    int i;
    for (i=0; i < ARRAY_SIZE; i++)
    {
        unsortedArray[i] = rand() % 100;
    }
    sort(unsortedArray, sortedArray, ARRAY_SIZE);
    printf("Unsorted array: \n");
    for (i=0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", unsortedArray[i]);
    }
    printf("\nSorted array: \n");
    for (i=0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", sortedArray[i]);
    }
}


int cmpfunc(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

void sort(int *unsorted, int *sorted, int size)
{
    assert(size % 2 == 0);
    pthread_t threads[3];
    int start1 = 0;
    int start2 = ARRAY_SIZE/2;
    pthread_create(&threads[0], NULL, qsortWorker, (void *) &start1);
    pthread_create(&threads[1], NULL, qsortWorker, (void *) &start2);
    int i;
    bool success;
    for (i=0; i < 2; i++)
    {
            success = pthread_join(threads[i], NULL);
            if (success != 0)
            {
                fprintf(stderr, "Error joining thread");
                return;
            }
    }
    arraysContainer arrays;
    arrays.start1 = start1;
    arrays.start2 = start2;
    pthread_create(&threads[2], NULL, mergeWorker, (void *) &arrays);
    success = pthread_join(threads[2], NULL);
}

void merge(int *arr1, int size1, int *arr2, int size2, int *merged)
{
    int i,j,k;
    i = j = k = 0;
    while (i < size1 && j < size2)
    {
        if (arr1[i] <= arr2[j])
        {
            merged[k] = arr1[i];
            i++;
        }
        else
        {
            merged[k] = arr2[j];
            j++;
        }
        k++;
    }
    
    while (i < size1)
    {
        merged[k] = arr1[i];
        i++; k++;
    }
    while (j < size2)
    {
        merged[k] = arr2[j];
        j++; k++;
    }
}

void *mergeWorker(void *param)
{
    arraysContainer *arrays = (arraysContainer*) param; 
    int start1 = arrays->start1;
    int start2 = arrays->start2;
    merge(unsortedArray + start1, ARRAY_SIZE/2, unsortedArray + start2, ARRAY_SIZE/2, sortedArray);
    pthread_exit(0);
}

void *qsortWorker(void *param)
{
    int start = *(int *) param;
    qsort(unsortedArray + start, ARRAY_SIZE/2, sizeof(int), cmpfunc);
    pthread_exit(0);
}
