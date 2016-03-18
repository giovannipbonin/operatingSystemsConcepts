#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{
    char *n = argv[1];
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        printf("ok");
        execlp("./collatz", "collatz", n, NULL);
        _exit(0);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
}
