/*
*   cat.c
*   This program will emulate Linux's cat program.
*   Right now it only does file and stdio.
*   Compiled with "gcc cat.c -o cat.exe -O3"
*/

#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <file/char[]>", argv[0]);
        return -1;
    }
    FILE *file = fopen(argv[1], "r");
    int c;
    if (file == NULL)
    {
        puts(argv[1]);
        while (c != '\0' && c != EOF)
        {
            c = getc(stdin);
            putc(c, stdout);
        }
    }
    else 
    {
        c = fgetc(file);
        while(c != '\0' && c != EOF)
        {
            putc(c, stdout);
            c = fgetc(file);
        }
    }
    return 0;
}