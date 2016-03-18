#include <stdlib.h>
#include <stdio.h>

#define MIN_PID 10
#define MAX_PID 20
#define SIZE MAX_PID - MIN_PID + 1

char *bit_map;

int allocate_map(void)
{
    bit_map = malloc(sizeof(char)*SIZE);
    if (bit_map == NULL && SIZE != 0) return -1;
    else 
    {
        int i;
        for (i=0; i < SIZE; i++)
        {
            bit_map[i] = '0';
        }
        return 1;
    }
}

int allocate_pid(void)
{
    int i;
    for (i=0; i < SIZE; i++)
    {
        if (bit_map[i] == '0')
        {
            bit_map[i] = '1';
            return MIN_PID + i;
        }
    }
    return 1;
}

void release_pid(int pid)
{
    if (pid <= MAX_PID && pid >= MIN_PID)
    {
        int index = pid - MIN_PID;
        bit_map[index] = '0';
    }
}



