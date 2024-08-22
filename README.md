# alloc-leak-finder
 simple memory leaks finder, uses my list data structure for keeping track of every allocation/free
 can be enabled with
  
 ```
 #define DEBUGALLOC
 #include "leakfinder.h"
 ```

this lib simply redefines malloc and free to two debugging functions.  
redefined `malloc(size)` simply stores in a list all allocations.  
redefined `free(mem)` removes from the list the record corresponding to the freed memory.  
`check_mem_leaks` macro prints to terminal the whole list contents.  
If there's still some allocated memory it'll be printed.  
This macro also becomes `#define check_mem_leaks ` if DEBUGALLOC is not defined   
