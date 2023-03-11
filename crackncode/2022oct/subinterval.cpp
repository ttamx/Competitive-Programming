#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n,q;
long long a[N],qs[N],lr[N],rl[N],dp[N];

//lr[n] = sigma(i=1->n,i*a[i])

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> q;
	bool cheat=true;
	for(int i=1;i<=n;++i){
		cin >> a[i];
		qs[i]+=qs[i-1]+a[i];
	}
	long long sum=0;
	for(int i=1;i<=n;++i){
		lr[i]=lr[i-1]+(a[i]*i);
		dp[i]=dp[i-1]+lr[i];
	}
	for(int i=1;i<=n;++i){
		rl[i]=rl[i-1]+qs[i];
	}
	while(q--){
		int l,r;
		cin >> l >> r;
		long long s=r-l+1;
		long long ans=0;
		ans=dp[r]-dp[l-1]-(s*lr[l-1])-((l-1)*(rl[r]-rl[l-1]-(s*qs[l-1])));
		cout << ans << '\n';
	}
}