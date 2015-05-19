#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void quick_sort(int *a, int l, int h);
int partition(int *a, int l, int h);
int find_pivot(int *a, int l, int h);
int get_median(int *a, int *med);

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
	int p, c;
	int i, j;
	int pivot;

	p = find_pivot(a, l, h);
	c = a[l]; a[l] = a[p]; a[p] = c;
	i = l, j = h+1, pivot = a[l];
	while(i+1 != j) {
		if (a[i+1] < pivot) i++;
		else {
			c = a[i+1];
			a[i+1] = a[--j];
			a[j] = c;
		}
	}
	a[l] = a[i]; a[i] = pivot;

	return i;
}

int find_pivot(int *a, int l, int h)
{
	int tmp[3], med[3], p;
	int i, j;
	int n = h-l+1;
	int group_size = n/3;
	int unit = n/9;

	if (n < 3) p = l;
	else {
		// Get medians of groups
		if (group_size < 3) {
			med[0] = l;
			med[1] = med[0] + group_size;
			med[2] = med[1] + group_size;
		}
		else {
			// Median of group 1
			tmp[0] = l + n/18;
			tmp[1] = tmp[0]+unit;
			tmp[2] = tmp[1]+unit;
			med[0] = get_median(a, tmp);
			// Median of group 2
			tmp[0] = tmp[2]+unit;
			tmp[1] = tmp[0]+unit;
			tmp[2] = tmp[1]+unit;
			med[1] = get_median(a, tmp);
			// Median of group 3
			tmp[0] = tmp[2]+unit;
			tmp[1] = tmp[0]+unit;
			tmp[2] = tmp[1]+unit;
			med[2] = get_median(a, tmp);
		}
		// Get pivot from medians
		p = get_median(a, med);
	}

	return p;
}

int get_median(int *a, int *med)
{
	int i, j;
	int min, min_id;

	for(i = 0; i < 2; i++) {
		min = med[i];
		min_id = i;
		for(j = i + 1; j < 3; j++) {
			if (a[med[j]] < a[min]) {
				min = med[j];
				min_id = j;
			}
		}
		med[min_id] = med[i];
		med[i] = min;
	}

	return med[1];
}