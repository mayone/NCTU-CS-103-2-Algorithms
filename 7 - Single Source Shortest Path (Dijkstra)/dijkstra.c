#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_VERTICES 1000


int adj[MAX_NUM_VERTICES][MAX_NUM_VERTICES];	// adjacency list
int weight[MAX_NUM_VERTICES][MAX_NUM_VERTICES];	// weight
int count[MAX_NUM_VERTICES];					// length of each list
int distance[MAX_NUM_VERTICES];					// distance from source
int visited[MAX_NUM_VERTICES];					// flag for visited node
int predecessor[MAX_NUM_VERTICES];
int path[MAX_NUM_VERTICES];

int main(int argc, char const *argv[])
{
	int i, j;
	int n, m;
	int range, speed;
	int src, dst;
	int u, v, w;
	int min, min_id;

	// get input
	scanf("%d", &n);	// num_vertices
	scanf("%d", &m);	// num_edges
	for(i = 0; i < m; i++)
	{
		scanf("%d %d %d", &u, &v, &w);	// endpoint1, endpoint2, weight_of_edge
		adj[u][count[u]] = v;
		adj[v][count[v]] = u;
		weight[u][count[u]] = w;
		weight[v][count[v]] = w;
		count[u]++;
		count[v]++;
	}
	scanf("%d", &range);
	scanf("%d", &speed);
	scanf("%d", &src);
	scanf("%d", &dst);

	// initialize
	for(i = 0; i < n; i++)
	{
		distance[i] = 1e9;	// initialize distance with INF
		predecessor[i] = -1;
	}

	distance[src] = 0;
	for(i = 0; i < n; i++)
	{
		// Extract min
		min = 1e9;
		for(j = 0; j < n; j++)
		{
			if (!visited[j] && distance[j] < min)
			{
				min = distance[j];
				min_id = j;
			}
		}

		// Relaxation
		for(j = 0; j < count[min_id]; j++)
		{
			if (weight[min_id][j] >= range) continue;
			if (distance[adj[min_id][j]] > distance[min_id] + weight[min_id][j])
			{
				distance[adj[min_id][j]] = distance[min_id] + weight[min_id][j];
				predecessor[adj[min_id][j]] = min_id;
			}
		}
		visited[min_id] = 1;
	}

	printf("Route:");
	for(i = dst, j = 0; predecessor[i] > -1; i = predecessor[i], j++)
	{
		path[j] = i;
		
	}
	path[j++] = src;
	for(i = j-1; i >= 0; i--)
	{
		printf(" %d", path[i]);
	}
	printf("\n");
	printf("Total distance: %d\n", distance[dst]);
	printf("Estimation time: %.2lf\n", (double)distance[dst] / speed);

	return 0;
}