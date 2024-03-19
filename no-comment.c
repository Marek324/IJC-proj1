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
            
            case 0: if(c=='/') stav=1;
                else if (c=='"') { stav=4; putchar(c); }
                else putchar(c);
                break;
            
            case 1: 
                if(c=='*') stav=2;
                else if(c=='/') putchar(c);
                else { stav=0; putchar('/'); putchar(c); }
                break;
            
            case 2: 
                if(c=='*') stav=3;
                break;
            
            case 3: 
                if(c=='/') { stav=0; putchar(' '); }
                else if(c!='*') stav=2;
                break;
            
            case 4: 
                if(c=='\\') stav=5;
                else if(c=='"') stav=0;
                putchar(c);
                break;
            
            case 5: stav=4;
                putchar(c);
                break;

            //TODO: pridat stavy
        
        } 
    } 
    if(stav!=0) fprintf(stderr, "Error\n");
    return 0;
}

