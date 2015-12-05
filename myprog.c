/* 
 * File:   myprog.c
 * Author: travismoretz
 *
 * Created on September 10, 2015, 3:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function prototype
void print_param(char[], int);
/*
 * 
 */
int myprog(int argc, char** argv) {

// loop though each argument and call print_param on each    
    for(int i = 1; i < argc; i++) {
        int size = strlen(argv[i]);
        print_param(argv[i], size); 
    }

    return (EXIT_SUCCESS);
}

/*  This function will take a char array and int value indicating the length
 *  of the array as parameters.  Then print the char array, first iteration
 *  on char, second iteration two char, until all char have been printed. 
 */ 
void print_param(char arg[], int arraySize) {
    
    for(int x = 1; x <= arraySize ; x++) {
            printf("%.*s\n", x, arg);   
        }
  
}
