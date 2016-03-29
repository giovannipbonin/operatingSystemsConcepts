#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_LINE 80 /* The maximum length command */
#define MAX_HISTORY 10

int parseCommand(char *command, char **args);

int main(void)
{
    char *args[MAX_LINE/2 + 1];
    char history[MAX_HISTORY][MAX_LINE];
    int countHistory[MAX_HISTORY];
    int currentCommand = 0;
    char input[MAX_LINE];
    bool concurrent;
    int should_run = 1;
    int i;
    pid_t pid;

    while (should_run)
    {
        concurrent = false;
        // Read user input
        printf("osh> "); 
        fflush(stdout);
        fgets(input, MAX_LINE, stdin);
        countHistory[currentCommand % MAX_HISTORY] = currentCommand;
        i = parseCommand(input, args);
        if(strcmp(args[0], "exit") == 0)
        {
            should_run = 0;
            return 0;
        }
        else if(strcmp(args[0], "history") == 0)
        {
            int j;
            for (j=0; j < (currentCommand % 10); j++)
            {
                printf("%d %s", countHistory[j], history[j]);
            }
        }
        else if(args[0][0] == '!')
        {
            if (args[0][1] == '!')
            {
                if (currentCommand == 0)
                {
                    fprintf(stderr, "Error, no previous command\n");
                }
                else
                {
                    strcpy(input, history[(currentCommand - 1) % MAX_HISTORY]);
                    i = parseCommand(input, args);        
                }
            }
            else
            {
                int count = (int)args[0][1] - '0';
                if (count < currentCommand)
                {
                    strcpy(input, history[count]);
                    i = parseCommand(input, args);
                }
                else
                {
                    fprintf(stderr, "Error, no previous command for this number\n");
                }
            }
        }
        if (strcmp(args[i-1], "&") == 0)
        {
           concurrent = true; 
           args[i-1] = NULL;
        }
        strcpy(history[currentCommand % MAX_HISTORY], input); 
        currentCommand++;
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
            if (!concurrent)
            {
                waitpid(pid, NULL, 0);
            }
        }
    }
    return 0;
}


int parseCommand(char *command, char **args)
{
    char *copyCommand = (char *)malloc(strlen(command) + 1);
    strcpy(copyCommand, command);
    int i = 0;
    char *newArg;
    newArg = strtok(copyCommand, " ");
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
    return i;
}
