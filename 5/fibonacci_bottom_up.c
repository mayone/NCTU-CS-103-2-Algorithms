#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long unsigned int lluint;

lluint f[50];	// need to be global to avoid violating memory limit

lluint fib(int n);

int main(int argc, char const *argv[])
{
	int n;
	lluint ans;

	scanf("%d", &n);

	ans = fib(n);

	printf("%llu\n", ans);

	return 0;
}

lluint fib(int n)
{
	int i;

	f[0] = 0;
	f[1] = 1;
	for(i = 2; i <= n; i++) {
		f[i] = f[i-2] + f[i-1];
	}

	return f[n];
}