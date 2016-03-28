#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define MAX_LINE 80 /* The maximum length command */

int main(void)
{
    char *args[MAX_LINE/2 + 1];
    char input[MAX_LINE];
    int should_run = 1;

    while (should_run)
    {
        // Read user input
        printf("osh> "); 
        fflush(stdout);
        fgets(input, MAX_LINE, stdin);
        char *newArg;
        int i = 0;
        newArg = strtok(input, " ");
        while (newArg != NULL)
        {
            args[i] = newArg;
            i++;
            newArg = strtok(NULL, " ");
        }
        printf("%s", args[0]);
        if (strcmp(args[0], "exit\n") == 0)
        {
            should_run = 0;
        }
    }
    return 0;
}
