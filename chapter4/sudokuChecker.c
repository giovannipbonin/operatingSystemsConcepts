#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool checkArray(int arr[])
{
    int bitmap = 0;
    int i;
    for (i=0; i < 9; i++)
    {
        bitmap = bitmap | (int)pow(2, arr[i] - 1);
    }
    if (bitmap == 511) return true;
    return false;
}


int main()
{

}
