#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll c[25];
bool can=true;

ll sol(ll w,int d){
    if(w<=0)can=false;
    if(!can)return -1;
	if(d<=1)return w;
	w=w*2+1-c[d];
	if(w&1)return sol(w/2,d-1)+sol(w/2+1,d-1);
	else return 2*sol(w/2,d-1);
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	ll w;
	cin >> n >> w;
	for(int i=2;i<=n;++i){
		cin >> c[i];
	}
	ll ans=sol(w,n);
	if(can)cout << ans;
	else cout << -1;
	return 0;
}
