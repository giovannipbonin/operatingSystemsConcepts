#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define BUFFER_SIZE 64
#define READ_END 0
#define WRITE_END 1

char reverseCase(char ch)
{
    if (ch >= 'A' && ch <= 'Z') ch = ch + 32;
    else if (ch >= 'a' && ch <= 'z') ch = ch - 32;
    return ch;
}
int main(void)
{
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd1[2], fd2[2];
    pid_t pid;

    /* create the pipe */
    if (pipe(fd1) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    if (pipe(fd2) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }


    /* Fork a child process */

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid > 0)
    {
        close(fd1[READ_END]);
        close(fd2[WRITE_END]);
        write(fd1[WRITE_END], write_msg, strlen(write_msg) + 1);
        close(fd1[WRITE_END]);
        waitpid(pid, NULL, 0);
        read(fd2[READ_END], read_msg, BUFFER_SIZE);
        close(fd2[READ_END]);
        printf("Parent read %s", read_msg);
    }
    else
    {
        close(fd2[READ_END]);
        close(fd1[WRITE_END]);
        read(fd1[READ_END], read_msg, BUFFER_SIZE);
        close(fd1[READ_END]);
        int len = strlen(read_msg);
        int i;
        for (i=0; i < len; i++)
        {
            write_msg[i] = reverseCase(write_msg[i]); 
        }
        write(fd2[WRITE_END], write_msg, strlen(write_msg) + 1);
        close(fd2[WRITE_END]);
        _exit(0);
    }
    return 0;
}
