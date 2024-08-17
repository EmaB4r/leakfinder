#ifndef MYALLOC_H
#define MYALLOC_H

#ifdef DEBUGALLOC
    #include <stddef.h>
    #include <stdlib.h>
    void * deb_malloc(size_t size, unsigned int line , char*file);
    void deb_free(void * mem, unsigned int line , char*file);
    void print_leaks();
    #define malloc(x) deb_malloc(x,__LINE__, __FILE__)
    #define free(x) deb_free(x,__LINE__, __FILE__)
    #define check_mem_leaks print_leaks()
#else
    #define check_mem_leaks
#endif

#endif