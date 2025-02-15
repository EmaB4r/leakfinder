#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dep/list.h"

#undef malloc
#undef calloc
#undef realloc
#undef free

typedef struct _allocation{
    void * mem;
    int line;
    char filename[50];
    size_t size;
} allocation;

int freecmp(allocation* alloc, void * mem){
    return alloc->mem-mem;
}

list_t allocations={.n_elements=-1};

void deb_free(void * mem, unsigned int line , char*file){
    list_remove(&allocations, (int (*)(void*, void *))freecmp, mem);
    free(mem);;
}

void * deb_malloc(size_t size, unsigned int line , char*file){
    if(allocations.n_elements==-1) allocations=list_init();
    void* mem = malloc(size);
    allocation alloc = {
        .mem = mem,
        .line=line,
        .size=size
    };
    strcpy(alloc.filename, file);
    LIST_INS_TAIL(&allocations, alloc);
    return mem;
}
void * deb_calloc(size_t n, size_t size, unsigned int line , char*file){
    if(allocations.n_elements==-1) allocations=list_init();
    void* mem = calloc(n, size);
    allocation alloc = {
        .mem = mem,
        .line=line,
        .size=size
    };
    strcpy(alloc.filename, file);
    LIST_INS_TAIL(&allocations, alloc);
    return mem;
}

void * deb_realloc(void * p, size_t size, unsigned int line , char*file){
    if(allocations.n_elements==-1) allocations=list_init();
    void* mem = realloc(p, size);
    deb_free(p, 0, NULL);
    allocation alloc = {
        .mem = mem,
        .line=line,
        .size=size
    };
    strcpy(alloc.filename, file);
    LIST_INS_TAIL(&allocations, alloc);
    return mem;
}


void allocation_print(allocation* alloc){
    printf("still allocated %luB at line %d in %s\n", alloc->size, alloc->line, alloc->filename);
}


void print_leaks(){
    list_print(&allocations, (void (*) (void*))allocation_print);
}
