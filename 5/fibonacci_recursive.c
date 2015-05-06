#include <stdio.h>
#include <stdlib.h>

typedef long long unsigned int lluint;

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
	if (n < 2) return n;
	else return fib(n-2) + fib(n-1);
}