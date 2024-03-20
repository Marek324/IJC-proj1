/*
*   no-comment.c
*   Marek Hric 
*   259715
*   xhricma00
*/

#include "error.h"
#include <stdio.h>

int main(int argc, char *argv[]){
    int stav = 0;
    int c;

    //TODO: argument handling

    while ((c=getchar()) != EOF) {
        switch(stav) {
            
            case 0: 
                if(c=='/') {
                    stav=1;
                }
                else if (c=='"') { 
                    stav=6; 
                    putchar(c); 
                }
                else if(c=='\''){
                    stav=7;
                    putchar(c);
                }
                else {
                    putchar(c);
                }
                break;
            
            case 1: 
                if(c=='/') {
                    stav=2;
                }
                else if (c=='*'){
                    stav = 4;
                }
                else {
                    stav = 0;
                    putchar('/');
                    putchar(c);
                }
                break;
            
            case 2: 
                if(c=='\\'){
                    stav = 3;
                } else if(c == '\n'){
                    stav = 0;
                    putchar('\n');
                }
                break;
            
            case 3: 
                if(c != '\\') {
                    stav = 2;
                }
                break;
            
            case 4: 
                if(c == '*'){
                    stav = 5;
                    break;
                } 
                break;
            
            case 5: 
                if(c != '*' && c != '/'){
                    stav = 4;
                } else if (c == '/'){
                    stav = 0;
                    putchar(' ');
                }
                break;

            case 6: 
                if(c == '"'){
                    stav = 0;
                    putchar('"');
                } else {
                    putchar(c);
                }
                break;

            case 7: 
                if(c == '\''){
                    stav = 0;
                    putchar('\'');
                } else {
                    putchar(c);
                }
                break;
        
        } 
    } 
    if(stav!=0) fprintf(stderr, "Error\n");
    return 0;
}

