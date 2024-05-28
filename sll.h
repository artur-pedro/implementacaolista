#ifndef Sll_h
#define Sll_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
typedef struct sllnode Sllnode;
typedef struct sllist Sllist;
Sllist *sllCreate (void); 
int sllDestroy (Sllist *l);
void *sllGetfirst( Sllist *l);
void *sllGetnext(Sllist *l);
int sllInsertAsLast(Sllist *l,void* data);
void *sllRemovelast( Sllist *l); 
void *sllQuery(Sllist *l, void *key, int(*cmp)(void*,void*));
void *sllRemoveSpec(Sllist *l, void *key,int(*cmp)(void*,void*));
#endif