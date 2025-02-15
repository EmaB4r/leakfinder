#ifndef MYALLOC_H
#define MYALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEBUGALLOC
    #include <stddef.h>
    #include <stdlib.h>
    void * deb_malloc(size_t size, unsigned int line , const char*file);
    void * deb_calloc(size_t n, size_t size, unsigned int line , const char*file);
    void * deb_realloc(void * p, size_t size, unsigned int line , const char*file);
    void deb_free(void * mem, unsigned int line , const char*file);
    void print_leaks();
    #define malloc(x) deb_malloc(x,__LINE__, __FILE__)
    #define calloc(x, y) deb_calloc(x,y,__LINE__, __FILE__)
    #define realloc(x,y) deb_realloc(x,y,__LINE__, __FILE__)
    #define free(x) deb_free(x,__LINE__, __FILE__)
    #define check_mem_leaks print_leaks()
#else
    #define check_mem_leaks
#endif

#ifdef __cplusplus
}
#endif

#endif