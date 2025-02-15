#include "intalloc.h"
#include <stdlib.h>

int * int_malloc(){
    return (int*)malloc(sizeof(int));
} 

int * int_realloc(int *i, size_t vec_len){
    return realloc (i, sizeof(int)*vec_len);
}