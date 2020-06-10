#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"arraylist.h"
#include"sort.h"

ArrayList createArrayList(int capacity)
{
	ArrayList l;
	l = (ArrayList)malloc(sizeof(ArrayList_t));
	if(l != NULL) {
		l->list = (void **)malloc(capacity*sizeof(void *));
		if(l->list != NULL) {
			l->size = 0;
			l->capacity = capacity;
		}
		else {
			free(l);
			l = NULL;
		}
	}
	return l;
}

void destroyArrayList(ArrayList l)
{
	free(l->list);
	free(l);
}

int isArrayListFull(ArrayList l)
{
	return l->size == l->capacity;
}

int isArrayListEmpty(ArrayList l)
{
	return l->size == 0;
}

int insertArrayList(ArrayList l, void *e, int index)
{
	void **nlist;
	int ncapacity;
	if(index >= 0 && index <= l->size) {
		if(isArrayListFull(l)) {
			ncapacity = l->capacity * 2;
			nlist = realloc(l->list, ncapacity * sizeof(void *));
			if(nlist != NULL) {
				//shift elements between index and l->size-1 to right by 1
				memmove(&nlist[index]+1, &nlist[index], (l->size - index)*sizeof(void *));

				l->list = nlist;
				l->capacity = ncapacity;
				l->size++;
				l->list[index] = e;
			}
			else {
				nlist = (void **)malloc(ncapacity * sizeof(void *));
				if(nlist != NULL) {
					//copy elements while shifting elements between index and l->size-1 to right by 1
					memcpy(nlist, l->list, index * sizeof(void *));
					memcpy(&nlist[index]+1, &l->list[index], (l->size - index)*sizeof(void *));
					free(l->list);

					l->list = nlist;
					l->capacity = ncapacity;
					l->size++;
					l->list[index] = e;
				}
				else {
					index = -index;
				}
			}
		}
		else {
			//shift elements between index and l->size-1 to right by 1
			memmove(&l->list[index]+1, &l->list[index], (l->size - index)*sizeof(void *));

			l->size++;
			l->list[index] = e;
		}
	}
	else {
		index = -index;
	}
	return index;
}

void *deleteArrayList(ArrayList l, int index)
{
	void *e;
	int ncapacity;
	void **nlist;
	e = NULL;
	if(!isArrayListEmpty(l) && index >= 0 && index < l->size) {
		e = l->list[index];
		l->size--;

		//shift elements between index+1 and l->size to left by 1
		memmove(&l->list[index], &l->list[index]+1, (l->size - index)*sizeof(void *));

		ncapacity = l->capacity / 2;
		if(l->size <= ncapacity && ncapacity > 0) {
			nlist = realloc(l->list, ncapacity * sizeof(void *));
			if(nlist != NULL) {
				l->list = nlist;
				l->capacity = ncapacity;
			}
			else {
				nlist = (void **)malloc(ncapacity * sizeof(void *));
				if(nlist != NULL) {
					//copy elements
					memcpy(nlist, l->list, l->size * sizeof(void *));
					free(l->list);
					l->list = nlist;
					l->capacity = ncapacity;
				}
			}
		}
	}
	return e;
}

//generic function which uses function pointers to print elements.
void fprintfArrayList(FILE *fp, ArrayList l, void (*print)(FILE *, void *))
{
	int i;
	fprintf(fp, "size:%d capacity:%d\n", l->size, l->capacity);
	for(i=0; i < l->size; i++) {
		print(fp, l->list[i]);
	}
	fprintf(fp, "\n");
}

//generic bubble sort implementation for ArrayList
void bubbleSortArrayList(ArrayList l, int (*compare)(void *, void *))
{
	bubble_sort(l->list, l->size, compare);
}

