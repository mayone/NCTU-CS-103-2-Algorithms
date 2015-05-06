#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long unsigned int lluint;

lluint fib(int n, lluint *cache);

int main(int argc, char const *argv[])
{
	int n;
	lluint *cache;
	lluint ans;

	scanf("%d", &n);
	cache = (lluint *)calloc(sizeof(lluint), n+1);	// zero-initialized
	memset(cache, -1, (n+1) * sizeof(lluint));
	cache[0] = 0;
	cache[1] = 1;

	ans = fib(n, cache);

	printf("%llu\n", ans);

	free(cache);

	return 0;
}

lluint fib(int n, lluint *cache)
{
	if (cache[n] != -1) return cache[n];
	else return cache[n] = fib(n-2, cache) + fib(n-1, cache);
}