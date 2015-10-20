#include <stdio.h>
#include <stdlib.h>

int find_peak(int *a, int l, int h);

int main(int argc, char const *argv[])
{
	int i, n;
	int *a;
	int peak;

	//printf("Length of array: ");
	scanf("%d", &n);
	a = (int *)malloc(sizeof(int) * n);
	//printf("Content of array: ");
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	peak = find_peak(a, 0, n-1);

	//printf("peak = %d\n", peak);
	printf("%d\n", peak);

	free(a);

	return 0;
}

int find_peak(int *a, int l, int h)
{
	int m = (l+h)/2;

	if (l == h) {
		return a[m];
	}
	else if ((m-1) >= 0 && a[m] < a[m-1]) {
		return find_peak(a, l, m-1);
	}
	else if (a[m] < a[m+1]) {
		return find_peak(a, m+1, h);
	}
	else {
		return a[m];
	}
}