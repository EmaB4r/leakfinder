// EXAMPLE 1
// you can see how, by simply including the header and definind DEBUGALLOC
// you can check if in THIS FILE ONLY you have some memory leak
// 
// check makefile on how to compile


#include <stdio.h>
#include <stdlib.h>
#define LEAKFINDER
#include "../../leakfinder.h"

int main(){
    char* c = malloc(1); //will leak both first and second check
    check_mem_leaks;
    putc('\n', stdout);
    char* d = malloc(1); //wont leak
    char* e = malloc(1); //will leak second check
    free(d);
    check_mem_leaks;
}