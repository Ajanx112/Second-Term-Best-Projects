#ifndef ___SORT_H___
#define ___SORT_H___

void swap(void **x, void **y);
void bubble_sort(void **a, int n, int (*compare)(void *, void *));

#endif
