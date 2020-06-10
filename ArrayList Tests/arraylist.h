#ifndef ___ARRAYLIST_H___
#define ___ARRAYLIST_H___

#include<stdio.h>

typedef struct ArrayList_s {
	void **list;
	int size;
	int capacity;
} ArrayList_t, *ArrayList;

ArrayList createArrayList(int capacity);
void destroyArrayList(ArrayList l);
int isArrayListFull(ArrayList l);
int isArrayListEmpty(ArrayList l);
int insertArrayList(ArrayList l, void *e, int index);
void *deleteArrayList(ArrayList l, int index);
void fprintfArrayList(FILE *fp, ArrayList l, void (*print)(FILE *, void *));
void bubbleSortArrayList(ArrayList l, int (*compare)(void *, void *));

#endif

