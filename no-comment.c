// no-comment.c
// Řešení IJC-DU1, příklad b), 20.3.2024
// Autor: Marek Hric, FIT
// Přeloženo: gcc 13.2.0

#define MAX_ARGS 2

#include "error.h"
#include <stdio.h>

int main(int argc, char *argv[]){

    if (argc > MAX_ARGS) return 0;

    FILE* in_stream;

    if (argc == 1){
        in_stream = stdin;
    } else {
        in_stream = fopen(argv[1], "r");

        if (in_stream == NULL){
            fprintf(stderr, "Error: file can't be open"); //TODO: pouzit error_exit z error.h
            return 1;
        }
    }
    
    int stav = 0;
    int c;

    while ((c = getchar()) != EOF) {
        switch(stav) {
            
            case 0: 
                if (c == '/'){
                    stav = 1;
                } else if (c == '"'){ 
                    stav = 6; 
                    putchar(c); 
                } else if (c == '\''){
                    stav = 7;
                    putchar(c);
                } else {
                    putchar(c);
                }
                break;
            
            case 1: 
                if (c == '/') {
                    stav = 2;
                } else if (c == '*'){
                    stav = 4;
                } else {
                    stav = 0;
                    putchar('/');
                    putchar(c);
                }
                break;
            
            case 2: 
                if (c == '\\'){
                    stav = 3;
                } else if (c == '\n'){
                    stav = 0;
                    putchar('\n');
                }
                break;
            
            case 3: 
                if (c != '\\'){
                    stav = 2;
                }
                break;
            
            case 4: 
                if (c == '*'){
                    stav = 5;
                } 
                break;
            
            case 5: 
                if (c != '*' && c != '/'){
                    stav = 4;
                } else if (c == '/'){
                    stav = 0;
                    putchar(' ');
                }
                break;

            case 6: 
                if (c == '"'){
                    stav = 0;
                    putchar('"');
                } else {
                    putchar(c);
                }
                break;

            case 7: 
                if (c == '\''){
                    stav = 0;
                    putchar('\'');
                } else {
                    putchar(c);
                }
                break;
        
        }  //TODO: prerobit automat, zabudol som na \' a \" v stringoch
    } 
    if(stav!=0) {
        fprintf(stderr, "Error\n"); //TODO: pouzit error_exit
        return 1;
    }
    return 0;
}

