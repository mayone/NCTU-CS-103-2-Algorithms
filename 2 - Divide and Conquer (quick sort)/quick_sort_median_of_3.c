#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void quick_sort(int *a, int l, int h);
int partition(int *a, int l, int h);

int main(int argc, char const *argv[])
{
	int i, n;
	int *a;
	srand(time(NULL));

	//printf("Number of elements to sort: ");
	scanf("%d", &n);
	a = (int *)malloc(sizeof(int) * n);

	//printf("%d input elements: ", n);
	for(i = 0; i < n; i++) {
		scanf("%d", a+i);
	}

	quick_sort(a, 0, n-1);

	// Output result
	printf("%d", a[0]);
	for(i = 1; i < n; i++) {
		printf(" %d", a[i]);
	}
	printf("\n");

	// Memory free
	free(a);

	return 0;
}

void quick_sort(int *a, int l, int h)
{
	int m;

	if (l < h) {
		m = partition(a, l, h);
		quick_sort(a, l, m-1);
		quick_sort(a, m+1, h);
	}
}

int partition(int *a, int l, int h)
{
	int r, count = 0;
	int p_id[3], p;
	int pivot;
	int i, j;
	int n = h-l+1;
	int min, min_id;
	int *flag = (int *)malloc(sizeof(int) * n);
	for(i = 0; i < n; i++) flag[i] = 0;

	// Get pivot
	if (n < 3) p = l;
	else {
		while(count < 3) {
			r = rand() % n;
			if (flag[r] == 0) {
				flag[r] = 1;
				p_id[count++] = l+r;
			}
		}
		for(i = 0; i < 2; i++) {
			min = p_id[i];
			min_id = i;
			for(j = i + 1; j < 3; j++) {
				if (a[p_id[j]] < a[min]) {
					min = p_id[j];
					min_id = j;
				}
			}
			p_id[min_id] = p_id[i];
			p_id[i] = min;
		}
		p = p_id[1];
	}

	// Partition
	r = a[l]; a[l] = a[p]; a[p] = r;
	i = l, j = h+1, pivot = a[l];
	while(i+1 != j) {
		if (a[i+1] < pivot) i++;
		else {
			r = a[i+1];
			a[i+1] = a[--j];
			a[j] = r;
		}
	}
	a[l] = a[i]; a[i] = pivot;
	
	free(flag);

	return i;
}