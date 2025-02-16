# leakfinder
 This library is able to intercept all `malloc`, `calloc`, `realloc` and `free`,  
 and keep track of all allocations/deallocations.  

 to know what is still allocated you need to write `check_mem_leaks;` to get something like:  
 `FILE:LINE: allocated M Bytes`  
 `FILE:LINE: allocated N Bytes`   
 `Total leaking memory: M+N Bytes`  
 
 keep in mind that this library only knows what allocations are not yet freed,  
 it cannot know what that memory is used for.
 
 
# How to use  
 can be enabled for a single file by doing:
 ```
 #define DEBUGALLOC
 #include "./leakfinder.h"
 // DO STUFF
 check_mem_leaks;
 ```  
 Or globally by compiling with:  
 `gcc  -DDEBUGALLOC -include ./leakfinder.h main.c ./leakfinder.c whatever.c `
 
 Thanks to [MrGerman](https://github.com/pfhaupt) for code testing and some code fixes