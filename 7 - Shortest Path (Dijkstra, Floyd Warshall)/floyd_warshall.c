#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTICES 5
#define MAX_NUM_VERTICES 1000
#define INF 1000


int D[NUM_VERTICES][NUM_VERTICES];	// distance between two vertices
int P[NUM_VERTICES][NUM_VERTICES];	// predecessor

int main(int argc, char const *argv[])
{
	int i, j, k;
	int n = NUM_VERTICES;

	// get input
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			scanf("%d", &D[i][j]);
			if (i != j && D[i][j] != INF)
			{
				P[i][j] = i+1;
			}
		}
	}

	for(k = 0; k < n; k++)
	{
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				if (D[i][j] > D[i][k] + D[k][j])
				{
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = P[k][j];
				}
			}
		}
	}

	// print distance
	for(i = 0; i < n; i++)
	{
		printf("%d", D[i][0]);
		for(j = 1; j < n; j++)
		{
			printf(" %d", D[i][j]);
		}
		printf("\n");
	}

	// print predecessor
	for(i = 0; i < n; i++)
	{
		if (P[i][0] == 0)
		{
			printf("NIL");
		}
		else
		{
			printf("%d", P[i][0]);
		}

		for(j = 1; j < n; j++)
		{
			if (P[i][j] == 0)
			{
				printf(" NIL");
			}
			else
			{
				printf(" %d", P[i][j]);
			}
		}
		printf("\n");
	}

	return 0;
}