#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



void collatz(int n)
{
    if (n < 0) return;
    else
    {
       do
       {
            printf("%d\n", n);
            if (n % 2 == 0) n = n/2;
            else n = 3*n + 1;
       } while (n != 1);
       printf("%d\n", 1);
    }
}


int main(int argc, char** argv)
{
   int n = strtol(argv[1], NULL, 10);
   collatz(n);
}


