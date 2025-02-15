#include "list.h"

#undef malloc
#undef calloc
#undef realloc
#undef free

int list_is_empty(list_t * list){
    return !list->n_elements;
}

list_t list_init(){
    list_t list;
    list.head=list.tail=NULL;
    list.n_elements=0;
    return list;
}

node_t * node_init(void*item, size_t item_size){
    node_t * node=malloc(sizeof(struct node_s));
    node->item=malloc(item_size);
    node->item_size=item_size;
    node->prev=node->next=NULL;
    memcpy(node->item, item, item_size);
    return node;
}

void node_free(node_t* node){
    free(node->item);
    free(node);
}

void list_ins_tail(list_t * list, void* item, size_t item_size){
    if(list_is_empty(list)){
        list->head=list->tail=node_init(item, item_size);
    }
    else{
        list->tail->next=node_init(item, item_size);
        list->tail->next->prev=list->tail;
        list->tail=list->tail->next;
    }
    list->n_elements++;
}

void list_ins_head(list_t * list, void* item, size_t item_size){
    if(list_is_empty(list)){
        list->head=list->tail=node_init(item, item_size);
    }
    else{
        list->head->prev=node_init(item, item_size);
        list->head->prev->next=list->head;
        list->head=list->head->prev;
    }
    list->n_elements++;
}

void list_append(list_t*dest, list_t*src){
    node_t * head=src->head;
    while (head!=NULL){
        list_ins_tail(dest, head->item, head->item_size);
        head=head->next;
    }
}

void list_print(list_t*list, void(*printfun)(void*item)){
    node_t * head=list->head;
    while(head!=NULL){
        printfun(head->item);
        head=head->next;
    }
}

void list_free_R(node_t * head){
    if (head == NULL) return;
    list_free_R(head->next);
    free(head->item);
    free(head);
}


void list_free(list_t * list){
    list_free_R(list->head);
    free(list);
}

int list_remove(list_t * list, int (* item_cmp)(void*, void*), void * key){
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
            node_free(to_del);
        }
        else node=node->next;
    }
    return found;
}