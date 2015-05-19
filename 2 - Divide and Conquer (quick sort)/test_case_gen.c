#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	int i;
	int n = 100;
	int *a;
	srand(time(NULL));

	if (argc > 1) {
		n = atoi(argv[1]);
	}

	// memory allocation
	a = (int *)malloc(sizeof(int) * n);

	// assign value
	for(i = 0; i < n; i++) {
		a[i] = rand() % n;
	}

	// assign value


	// output matrix
	printf("%d\n", n);
	for(i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	// memory free
	free(a);

	return 0;
}