#include "goldenland.cpp"
#include <cstdio>

int main(){
	int n, m, p;
	scanf("%d%d%d",&n,&m,&p);
	std::vector<int> a, b;
	int x;
	for(int i = 0; i < n; i++){
		scanf("%d",&x);
		a.push_back(x);
	}
	for(int i = 0; i < m; i++){
		scanf("%d",&x);
		b.push_back(x);
	}
	init_land(n, m, p, a, b);
	for(int i = 0; i < p; i++){
		int r1, c1, r2, c2;
		scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
		long long ans = answer_query(r1, c1, r2, c2);
		printf("%lld\n", ans);
	}
	return 0;
}
