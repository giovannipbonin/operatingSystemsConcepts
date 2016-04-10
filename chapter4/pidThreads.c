#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MIN_PID 300
#define MAX_PID 5000
#define SIZE MAX_PID - MIN_PID + 1
#define NUM_THREADS 100

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

void *pidWork(void *threadNumber)
{
    int pid = allocate_pid();
    int n = *((int *) threadNumber);
    int s = rand() % 10;
    printf("Thread, %d, has allocated pid: %d, now sleeping: %d seconds\n", n, pid, s);
    sleep(s);
    release_pid(pid);
    printf("Thread, %d, has released pid: %d\n", n, pid);
    pthread_exit(0);
}

int main(void)
{
    srand(time(NULL));
    int success = allocate_map();
    if (success == -1)
    {
        fprintf(stderr, "Error allocating map");
        return 1;
    }
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;
    for (i=0; i < NUM_THREADS; i++)
    {
        pthread_attr_init(&attr[i]);
        success = pthread_create(&threads[i], &attr[i], pidWork, (void *) &i);
        if (success != 0)
        {
            fprintf(stderr, "Error creating thread");
            return -1;
        }
    }
    for (i=0; i < NUM_THREADS; i++)
    {
        success = pthread_join(threads[i], NULL);
        if (success != 0)
        {
            fprintf(stderr, "Error joining thread");
            return -1;
        }
    }
    printf("Threads have been completed\n");
    exit(EXIT_SUCCESS);
}

