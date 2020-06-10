void swap(void **x, void **y)
{
	void *tmp;
	tmp = *y;
	*y = *x;
	*x = tmp;
}

//generic bubble sort implementation
void bubble_sort(void **a, int n, int (*compare)(void *, void *))
{
	int i, high;
	while(n != 0) {
		high = 0;
		for(i=0; i<=n-2; i++) {
			if(compare(a[i], a[i+1]) > 0) {
				swap(&a[i], &a[i+1]);
				high = i+1;
			}
		}
		n = high;
	}
}

