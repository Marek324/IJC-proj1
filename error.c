// error.c
// Řešení IJC-DU1, příklad b), 19.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0
// Definicia variadickych warning a error_exit funkcii

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void warning(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);

    va_end(args);
}

void error_exit(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);

    va_end(args);

    exit(1);
}