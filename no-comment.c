// no-comment.c
// Řešení IJC-DU1, příklad b), 20.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0

#define MAX_ARGS 2

#include "error.h"
#include <stdio.h>

int main(int argc, char *argv[])
{

    if (argc > MAX_ARGS)
        return 1;

    FILE *in_stream;

    if (argc == 1)
    {
        in_stream = stdin;
    }
    else
    {
        in_stream = fopen(argv[1], "r");

        if (in_stream == NULL)
            error_exit("File not readable");
    }

    int stav = 0;
    int c;

    while ((c = fgetc(in_stream)) != EOF)
    {
        switch (stav)
        {

        case 0:
            if (c == '/')
            {
                stav = 1;
            }
            else if (c == '"')
            {
                stav = 6;
                putchar(c);
            }
            else if (c == '\'')
            {
                stav = 8;
                putchar(c);
            }
            else
            {
                putchar(c);
            }
            break;

        case 1:
            if (c == '/')
            {
                stav = 2;
            }
            else if (c == '*')
            {
                stav = 4;
            }
            else
            {
                stav = 0;
                putchar('/');
                putchar(c);
            }
            break;

        case 2:
            if (c == '\\')
            {
                stav = 3;
            }
            else if (c == '\n')
            {
                stav = 0;
                putchar('\n');
            }
            break;

        case 3:
            if (c != '\\')
            {
                stav = 2;
            }
            break;

        case 4:
            if (c == '*')
            {
                stav = 5;
            }
            break;

        case 5:
            if (c != '*' && c != '/')
            {
                stav = 4;
            }
            else if (c == '/')
            {
                stav = 0;
                putchar(' ');
            }
            break;

        case 6:
            if (c == '"')
            {
                stav = 0;
            }
            else if (c == '\\')
            {
                stav = 7;
            }

            putchar(c);
            break;

        case 7:
            stav = 6;
            putchar(c);
            break;

        case 8:
            if (c == '\'')
            {
                stav = 0;
            }
            else if (c == '\\')
            {
                stav = 9;
            }
            putchar(c);
            break;

        case 9:
            stav = 8;
            putchar(c);
            break;
        }
    }

    if (stav >= 6 && stav <= 9)
        error_exit("Invalid input");

    return 0;
}
