#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int cache[1000][1000];

int compare(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

int cost(int *pos, int l, int h);

int main(int argc, char const *argv[])
{
	int i, j;
	int str_len;
	int num_cuts;
	int *cut_pos;
	int *pos;
	int min_cost;

	// get the inputs
	scanf("%d", &str_len);
	scanf("%d", &num_cuts);

	cut_pos = (int *)calloc(sizeof(int), num_cuts);
	pos = (int *)calloc(sizeof(int), num_cuts+2);

	for(i = 0; i < num_cuts; i++) {
		scanf("%d", cut_pos+i);
	}
	qsort(cut_pos, num_cuts, sizeof(int), compare);

	pos[0] = 0;
	for(i = 0; i < num_cuts; i++) {
		pos[i+1] = cut_pos[i];
	}
	pos[i+1] = str_len;

	min_cost = cost(pos, 0, num_cuts+1);
	printf("%d\n", min_cost);

	free(pos);
	free(cut_pos);

	return 0;
}

int cost(int *pos, int l, int h)
{
	int i;
	int min = INT_MAX;
	int sum;

	if (h == l+1) return 0;
	if (cache[l][h] != 0) return cache[l][h];
	for(i = l+1; i < h; i++) {
		sum = cost(pos, l, i) + cost(pos, i, h);
		if (sum < min) {
			min = sum;
		}
	}

	return cache[l][h] = (pos[h] - pos[l] + min);
}
