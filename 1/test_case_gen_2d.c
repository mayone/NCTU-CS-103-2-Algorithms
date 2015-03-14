#include <stdio.h>
#include <stdlib.h>

enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

int main(int argc, char const *argv[])
{
	int **mat;
	int i, j, x;
	int n = 10;
	int dir = RIGHT;

	if (argc > 1) {
		n = atoi(argv[1]);
	}

	// memory allocation
	mat = (int **)malloc(sizeof(int*) * n);
	for(i = 0; i < n; i++) {
		mat[i] = (int *)malloc(sizeof(int) * n);
	}

	// initialize
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			mat[i][j] = 0;
		}
	}

	// assign value
	x = n*n;
	i = j = 0;
	while(x > 0) {
		mat[i][j] = x--;
		switch(dir) {
			case UP :
				if (i-1 < 0 || mat[i-1][j] != 0) {
					dir = RIGHT;
					j += 1;
				}
				else {
					i -= 1;
				}
				break; 
			case DOWN :
				if (i+1 == n || mat[i+1][j] != 0) {
					dir = LEFT;
					j -= 1;
				}
				else {
					i += 1;
				}
				break;
			case LEFT :
				if (j-1 < 0 || mat[i][j-1] != 0) {
					dir = UP;
					i -= 1;
				}
				else {
					j -= 1;
				}
				break;
			case RIGHT :
				if (j+1 == n || mat[i][j+1] != 0) {
					dir = DOWN;
					i += 1;
				}
				else {
					j += 1;
				}
				break;
		}
	}

	// output matrix
	printf("%d\n", n);
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("%3d ", mat[i][j]);
		}
		printf("\n");
	}

	// memory free
	for(i = n-1; i >= 0; i--) {
		free(mat[i]);
	}
	free(mat);

	return 0;
}