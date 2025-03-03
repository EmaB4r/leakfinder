// EXAMPLE 2
// this example shows that it is possible to redefine the whole codebase malloc, calloc etc to the
// custom leakfinder allocator, able to keep track for you of all your allocations and frees,
// signaling, whenever you want, a leak
//
// !!check makefile for the compilation!!

#include "intalloc.h"
#include "charalloc.h"
#include <stdio.h>
int main(){
    char* c = char_calloc(); //will leak both first, second and third checks 
    check_mem_leaks;
    putc('\n', stdout);
    int * i = int_malloc(); //will leak this second check
    check_mem_leaks;
    putc('\n', stdout);
    int_realloc(i, 2); //will still leak but this time as 8 bytes
}
