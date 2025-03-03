// EXAMPLE 1
// you can see how, by simply including the header and defining LEAKFINDER,
// you can check if THIS FILE ONLY memory is leaking
// 
// !!check makefile on how to compile!!

#include <stdio.h>
#include <stdlib.h>
#define LEAKFINDER
#include "charalloc.h"
#include "../../leakfinder.h"

int main(){
    char* c = malloc(1);      //will leak during both first and second check
    check_mem_leaks;
    putc('\n', stdout);
    char* k = char_calloc();  //will not be tracked
    char* d = malloc(1);      //won't leak
    char* e = malloc(1);      //will leak during second check
    free(d);
}