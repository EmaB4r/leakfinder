#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#undef malloc
#undef calloc
#undef realloc
#undef free

// LIST DATA STRUCTURE SEGMENT

typedef struct node_s{
    struct node_s *prev;
    struct node_s *next;
    void * item;
    size_t item_size;
}node_t;

typedef struct list_s{
    node_t * head;
    node_t * tail;
    int n_elements;
}list_t;

#define LEAKFINDER_LIST_INS_TAIL(LIST, ITEM) leakfinder_list_ins_tail(LIST, &ITEM, sizeof(ITEM))
#define LEAKFINDER_LIST_INS_HEAD(LIST, ITEM) leakfinder_list_ins_head(LIST, &ITEM, sizeof(ITEM))

int leakfinder_list_is_empty(list_t * list){
    return !list->n_elements;
}

list_t leakfinder_list_init(){
    list_t list;
    list.head=list.tail=NULL;
    list.n_elements=0;
    return list;
}

node_t * leakfinder_node_init(void*item, size_t item_size){
    node_t * node=malloc(sizeof(struct node_s));
    node->item=malloc(item_size);
    node->item_size=item_size;
    node->prev=node->next=NULL;
    memcpy(node->item, item, item_size);
    return node;
}

void leakfinder_node_free(node_t* node){
    free(node->item);
    free(node);
}

void leakfinder_list_ins_tail(list_t * list, void* item, size_t item_size){
    if(leakfinder_list_is_empty(list)){
        list->head=list->tail=leakfinder_node_init(item, item_size);
    }
    else{
        list->tail->next=leakfinder_node_init(item, item_size);
        list->tail->next->prev=list->tail;
        list->tail=list->tail->next;
    }
    list->n_elements++;
}

void leakfinder_list_ins_head(list_t * list, void* item, size_t item_size){
    if(leakfinder_list_is_empty(list)){
        list->head=list->tail=leakfinder_node_init(item, item_size);
    }
    else{
        list->head->prev=leakfinder_node_init(item, item_size);
        list->head->prev->next=list->head;
        list->head=list->head->prev;
    }
    list->n_elements++;
}

void leakfinder_list_print(list_t*list, void(*printfun)(void*item)){
    node_t * head=list->head;
    while(head!=NULL){
        printfun(head->item);
        head=head->next;
    }
}

int leakfinder_list_remove(list_t * list, int (* item_cmp)(void*, void*), void * key){
    node_t* node=list->head, *to_del=NULL;
    int found=1;
    while(node!=NULL){
        if(!item_cmp(node->item, key)){
            found = 1;
            if(node==list->head){
                list->head=list->head->next;
                if(list->head!=NULL)list->head->prev=NULL;
                to_del=node;
                node=node->next;
            }
            else if(node==list->tail){
                list->tail=list->tail->prev;
                if(list->tail!=NULL)
                list->tail->next=NULL;
                to_del=node;
                node=node->next;
            }
            else{
                node->prev->next= node->next;
                node->next->prev=node->prev;
                to_del=node;
                node=node->next;    
            }
            list->n_elements--;
            leakfinder_node_free(to_del);
        }
        else node=node->next;
    }
    return found;
}


typedef struct _allocation{
    void * mem;
    int line;
    char filename[50];
    size_t size;
} allocation;

int freecmp(allocation* alloc, void * mem){
    return (char*)alloc->mem-(char*)mem;
}

list_t allocations={.n_elements=-1};

void deb_free(void * mem){
    leakfinder_list_remove(&allocations, (int (*)(void*, void *))freecmp, mem);
    free(mem);
}

void * deb_malloc(size_t size, unsigned int line , const char*file){
    if(allocations.n_elements==-1) allocations=leakfinder_list_init();
    void* mem = malloc(size);
    allocation alloc = {
        .mem = mem,
        .line=line,
        .size=size
    };
    strcpy(alloc.filename, file);
    LEAKFINDER_LIST_INS_TAIL(&allocations, alloc);
    return mem;
}
void * deb_calloc(size_t n, size_t size, unsigned int line , const char*file){
    if(allocations.n_elements==-1) allocations=leakfinder_list_init();
    void* mem = calloc(n, size);
    allocation alloc = {
        .mem = mem,
        .line=line,
        .size=size
    };
    strcpy(alloc.filename, file);
    LEAKFINDER_LIST_INS_TAIL(&allocations, alloc);
    return mem;
}

void * deb_realloc(void * p, size_t size, unsigned int line , const char*file){
    if(allocations.n_elements==-1) allocations=leakfinder_list_init();
    deb_free(p);
    void* mem = realloc(p, size);
    allocation alloc = {
        .mem = mem,
        .line=line,
        .size=size
    };
    strcpy(alloc.filename, file);
    LEAKFINDER_LIST_INS_TAIL(&allocations, alloc);
    return mem;
}


void allocation_print(allocation* alloc){
    printf("still allocated %zuB at line %d in %s\n", alloc->size, alloc->line, alloc->filename);
}


void print_leaks(){
    leakfinder_list_print(&allocations, (void (*) (void*))allocation_print);
}


