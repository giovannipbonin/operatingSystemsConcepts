#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    FILE *ifp, *ofp;
    char outputName[] = "destination";
    
    ifp = fopen(argv[1], "r");
    if (ifp == NULL)
    {
        fprintf(stderr, "File %s doesn't exist\n", argv[1]);
        exit(1);
    }
    ofp = fopen(outputName, "w");
    if (ofp == NULL)
    {
        fprintf(stderr, "Can't open output file\n");
        exit(1);
    }
    char currentChar;
    while ((currentChar = fgetc(ifp)) != EOF)
    {
        fputc(currentChar, ofp);
    }
    fclose(ofp);
    return 0;
}
