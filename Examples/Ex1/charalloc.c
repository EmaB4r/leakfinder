#include "charalloc.h"

char * char_calloc(){
    return (char*)calloc(1, sizeof(char));
} 

void char_free(char*c){
    free(c);
}