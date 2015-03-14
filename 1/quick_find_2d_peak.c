#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_peak(int **b, int l, int h, int n);

int main(int argc, char const *argv[])
{
	int i, j, n;
	int **b;
	int peak;

	//printf("Size of matrix: ");
	scanf("%d", &n);
	b = (int **)malloc(sizeof(int*) * n);
	for(i = 0; i < n; i++) {
		b[i] = (int *)malloc(sizeof(int) * n);
	}
	//printf("Content of matrix: ");
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			scanf("%d", &b[i][j]);
		}
	}

	peak = find_peak(b, 0, n-1, n);

	printf("%d\n", peak);

	for(i = n-1; i >= 0; i--) {
		free(b[i]);
	}
	free(b);

	return 0;
}

int find_peak(int **b, int l, int h, int n)
{
	int i, max_id = 0;
	int row = (l+h)/2;

	// find global min in the row
	for(i = 1; i < n; i++) {
		if (b[row][i] > b[row][max_id]) {
			max_id = i;
		}
	}

	// compare to up and down
	if ((row-1 >= 0) && b[row][max_id] < b[row-1][max_id]) {
		return find_peak(b, l, row-1, n);
	}
	else if ((row+1 < n) && b[row][max_id] < b[row+1][max_id]) {
		return find_peak(b, row+1, h, n);
	}
	else {
		return b[row][max_id];
	}
}