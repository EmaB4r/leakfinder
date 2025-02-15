# leakfinder
 This library is able to redefine some (or every) malloc, calloc, realloc and free to custom allocators,  
 also able to keep track of all the unfreed memory.  

 to know what is still allocated you need to write `check_mem_leaks;` to get something like:  
 `still allocated 8B at line 15 in main.c`  
 
 keep in mind that this library only knows what malloc() calls are still not freed
 
 
# How to use  
 can be enabled for a single file by doing:
 ```
 #define DEBUGALLOC
 #include "./leakfinder.h"
 ```  
 Or globally by compiling with:  
 gcc  -DDEBUGALLOC -include ./leakfinder.h main.c ./leakfinder.c ./dep/list.c whatever.c 