#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    const int SIZE = 8192;
    const char *name = "sMemory";
    void *ptr; 
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int n = strtol(argv[1], NULL, 10);
    int fd = shm_open("/memory", O_RDWR | O_CREAT, 0777);
    if (fd == -1) fprintf(stderr, "Open failed");
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        sprintf(ptr, "%d", n);
        ptr++;
        while (n > 1)
        {
                sprintf(ptr, ", ");
                ptr += 2;
                if (n % 2 == 0) n = n/2;
                else n = 3*n + 1;
                sprintf(ptr, "%d", n);
                int shift = log10(n) + 1;
                ptr += shift;
        }
        sprintf(ptr, "\n");
        _exit(0);
    }
    else
    {
        waitpid(pid, NULL, 0);
        shm_fd = shm_open(name, O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        printf("%s", (char*)ptr);
        shm_unlink(name);
        return 0;
    }
}
