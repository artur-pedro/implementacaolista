#include "sll.h"
typedef struct sllnode{
    void* data;
    struct sllnode *next;
}Sllnode;
typedef struct sllist{
    Sllnode* first;
    Sllnode* cur;
}Slllist;
Sllist *sllCreate (void){
    Sllist* l;
    l = (Sllist*)malloc(sizeof(Sllist));
    if(l != NULL){
        l->first = NULL;
        return l;
    }
    return NULL;
}
int sllDestroy (Sllist *l){
    if(l!=NULL){
        if(l->first == NULL){
            free(l);
            return TRUE;
        }
    }
    return FALSE;
}
void *sllGetfirst(Sllist *l) {
    if (l != NULL && l->first != NULL) {
        l->cur = l->first;  
        return l->cur->data;  
    }
    return NULL;
}

void *sllGetnext(Sllist *l) {
    if (l != NULL && l->cur != NULL && l->cur->next != NULL) {
        l->cur = l->cur->next; 
        return l->cur->data;  
    }
    return NULL;
}
int sllInsertAsLast(Sllist *l, void* data){
    if(l != NULL){
        Sllnode *newnode;
        Sllnode *last;
        newnode = (Sllnode *) malloc(sizeof(Sllnode));
        if(newnode != NULL) {
            newnode->data = data;
            newnode->next = NULL;
            if(l->first == NULL) {
                l->first = newnode;
            }
            else{
                last =l->first;
                while (last->next != NULL) {
                    last = last->next;
                }
                last->next = newnode;
            }
        }
        return TRUE;
    }
    return FALSE;
}
void *sllRemovelast( Sllist *l){
    if(l != NULL){
        Sllnode *del;
        Sllnode *beforedel;
        void* data;
        if(l->first != NULL){
            del = l->first;
            if(del->next == NULL){
                data = del->data;
                l->first = NULL;
                free(del);
                return data; 
            }
            while(del->next != NULL){
                beforedel = del;
                del = del->next;
            }
            beforedel->next = NULL;
            data = del->data;
            free(del);
            return data;
        }
    }
    return NULL;
}
void* sllQuery(Sllist *l, void *key, int(*cmp)(void*, void*)) {
    Sllnode *cur;
    if (l != NULL && key != NULL) {
        if (l->first != NULL) {
            cur = l->first;
            int stat = cmp(key, cur->data);
            while (stat != TRUE && cur->next != NULL) {
                cur = cur->next;
                stat = cmp(key, cur->data);
            }
            if (stat == TRUE) {
                return cur->data;
            }
        }
    }
    return NULL;
}
void *sllRemoveSpec(Sllist *l, void *key, int(*cmp)(void *, void*)) {
    Sllnode *spec, *prev;
    int stat;
    void *data;
    if (l != NULL) {
        if (l->first != NULL) {
            spec = l->first;
            prev = NULL;
            stat = cmp(key, spec->data);
            while (stat != TRUE && spec->next != NULL) {
                prev = spec;
                spec = spec->next;
                stat = cmp(key, spec->data);
            }
            if (stat == TRUE) {
                data = spec->data;
                if (prev == NULL) {
                    l->first = spec->next;
                } else {
                    prev->next = spec->next;
                }
                if (l->cur == spec) {
                    l->cur = spec->next;
                }
                free(spec);
                return data;
            }
        }
    }
    return NULL;
}