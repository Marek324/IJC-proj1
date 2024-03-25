// error.h
// Řešení IJC-DU1, příklad b), 19.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0
// Deklaracia warning a error_exit funkcii

#ifndef ERROR_H
#define ERROR_H

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif // ERROR_H