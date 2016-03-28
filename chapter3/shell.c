#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_LINE 80 /* The maximum length command */

int main(void)
{
    char *args[MAX_LINE/2 + 1];
    char input[MAX_LINE];
    int should_run = 1;
    pid_t pid;

    while (should_run)
    {
        // Read user input
        printf("osh> "); 
        fflush(stdout);
        fgets(input, MAX_LINE, stdin);
        char *newArg;
        int i = 0;
        newArg = strtok(input, " ");
        while (1)
        {
            args[i] = newArg;
            i++;
            newArg = strtok(NULL, " ");
            if (newArg == NULL)
            {
                int strLen = strlen(args[i - 1]);
                args[i - 1][strLen - 1] = 0;
                args[i] = NULL;
                break;
            }
        }
        if (strcmp(args[0], "exit") == 0)
        {
            should_run = 0;
            return 0;
        }
        pid = fork();
        if (pid < 0)
        {
            fprintf(stderr, "Error creating child process");
        }
        else if (pid == 0)
        {
            execvp(args[0], args);
            _exit(0);
        }
        else
        {
            /*
            if (strcmp(args[i - 1], "&\n") == 0)
            {
                printf("works");
                waitpid(pid, NULL, 0);
            }*/
        }
    }
    return 0;
}
