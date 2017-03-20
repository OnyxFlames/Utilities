/*
*   cat.c
*   This program will emulate Linux's cat program.
*   Right now it only does file and stdio.
*   Compiled with "gcc cat.c -o cat.exe -O3"
*/

#include <stdio.h>
#include <string.h>

char line_numbers = 0;

int main(int argc, char* argv[])
{
    if(argc >= 2)
    {
        for(short i = 0; i < argc; i++)
        {
            if(strcmp(argv[i], "-l") == 0)
            {
                line_numbers = 1;
            }
        }
    }
    FILE *file = fopen(argv[1], "r");
    int c, line_num = 1;
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
            if(line_numbers && c == '\n' || c == '\r')
            {
                putc(c, stdout);
                printf("%d:\t", line_num++);
                c = fgetc(file);
            }
            else
            {
                if (line_numbers && line_num == 1)
                    printf("%d:\t", line_num++);
                putc(c, stdout);
                c = fgetc(file);
            }
        }
    }
    return 0;
}