#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int compare(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

int find_min_cost(int *pos, int n);

int get_cost(int **table, int *pos, int l, int h);

void show_table(int **table, int n);

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

	min_cost = find_min_cost(pos, num_cuts+1);
	printf("%d\n", min_cost);

	free(pos);
	free(cut_pos);

	return 0;
}

int find_min_cost(int *pos, int n)
{
	int i, j, min_cost;
	int **table;

	// create table
	table = (int **)calloc(sizeof(int *), n);
	for(i = 0; i < n; i++) {
		table[i] = (int *)calloc(sizeof(int), n);
	}

	// build table
	for(i = 1; i < n; i++) {
		for(j = i-1; j >= 0; j--) {
			table[j][i] = get_cost(table, pos, j, i);
		}
	}

	//show_table(table, n);

	min_cost = table[0][n-1];
	
	// release table
	for(i = n-1; i >= 0; i--) {
		free(table[i]);
	}
	free(table);

	return min_cost;
}

int get_cost(int **table, int *pos, int l, int h)
{
	int i;
	int min_segs_cost = INT_MAX;
	int segs_cost;

	for(i = l; i < h; i++) {
		segs_cost = table[l][i] + table[i+1][h];
		if (segs_cost < min_segs_cost) {
			min_segs_cost = segs_cost;
		}
	}

	return (pos[h+1] - pos[l]) + min_segs_cost;
}

void show_table(int **table, int n)
{
	int i, j;

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("%d\t", table[i][j]);
		}
		printf("\n");
	}
}