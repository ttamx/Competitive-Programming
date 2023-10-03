#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "trilib.h"

static int n;
static long long *x, *y;
static int queries=0;

static void init() {
	static int is_inited=0;
	if (is_inited)
		return;
	is_inited=1;
	assert(scanf("%d", &n)==1);
	x=(long long*)malloc((n+1)*sizeof(long long));
	y=(long long*)malloc((n+1)*sizeof(long long));
	for (int i=1; i<=n; i++)
		assert(scanf("%lld%lld", &x[i], &y[i])==2);
}

int get_n() {
	init();
	return n;
}

int is_clockwise(int a, int b, int c) {
	init();
	assert(a>=1 && a<=n);
	assert(b>=1 && b<=n);
	assert(c>=1 && c<=n);
	assert(a!=b && a!=c && b!=c);
	queries++;
        if(queries == 1000 * 1000 + 1)
            printf("Too many queries!");
	return (x[b]-x[a])*(y[c]-y[a])-(x[c]-x[a])*(y[b]-y[a])<0;
}

void give_answer(int s) {
	init();
	printf("%d\n", s);
}
