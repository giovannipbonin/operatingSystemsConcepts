#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 10000

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Please make sure 2 arguments have been passed");
        return 1;
    }
    int nameLen = strlen(argv[1]); 
    int fd[2];
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Error with fork()");
        return 1;
    }
    else if (pid == 0)
    {
        char filename[BUFFER_SIZE];
        char content[BUFFER_SIZE];
        close(fd[WRITE_END]);
        read(fd[READ_END], filename, nameLen + 1);
        close(fd[READ_END]);
        FILE *ifp = fopen(filename, "r");
        FILE *ofp = fopen(argv[2], "w");
        if (ifp == NULL)
        {
            fprintf(stderr, "File read failed");
            return 1;
        }
        if (ofp == NULL)
        {
            fprintf(stderr, "File read failed");
            return 1;
        }       
        char a;
        a = fgetc(ifp);
        while (a != EOF)
        {
            fputc(a, ofp);
            a = fgetc(ifp);
        } 
        fclose(ofp);
        fclose(ifp);
        _exit(0);        
    }
    else
    {
        close(fd[READ_END]);
        write(fd[WRITE_END], argv[1], nameLen + 1);
        close(fd[WRITE_END]);
        waitpid(pid, NULL, 0);
    }
    return 0;
}
