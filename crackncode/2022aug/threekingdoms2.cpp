#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<int,int,int> t3;

const int N=2e5+5;
const int K=1<<18+5;

int n,m,q;
int pa[N],l[N],r[N],a[N];
p2 k[N];
t3 t[N];
vector<int> res[N];

int fp(int u){
	if(u==pa[u])return u;
	return pa[u]=fp(pa[u]);
}

struct segtree{
	int t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=a[l]);
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=max(t[i*2],t[i*2+1]);
	}
	void build(){
		build(1,n,1);
	}
	int query(int l,int r,int i,int x,int y){
		if(l>y||r<x)return 0;
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
	}
	int query(int x,int y){
		return query(1,n,1,x,y);
	}
}s;

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m >> q;
	for(int i=1;i<=m;++i){
		auto &[x,y,z]=t[i];
		cin >> x >> y >> z;
	}
	for(int i=1;i<n;++i){
		l[i]=1,r[i]=m+1;
	}
	bool done;
	while(true){
		done=true;
		for(int i=1;i<n;++i){
			if(l[i]==r[i])continue;
			done=false;
			res[(l[i]+r[i])/2].emplace_back(i);
		}
		if(done)break;
		iota(pa,pa+n+1,0);
		for(int i=1;i<=m;++i){
			auto [x,y,z]=t[i];
			x=fp(x),y=fp(y),z=fp(z);
			pa[x]=z,pa[y]=z;
			for(auto j:res[i]){
				if(fp(j)==fp(j+1))r[j]=i;
				else l[j]=i+1;
			}
			res[i].clear();
		}
	}
	for(int i=1;i<n;i++)a[i]=l[i];
	s.build();
	for(int i=1;i<=q;++i){
		int x,y;
		cin >> x >> y;
		if(x==y)cout << 0 << '\n';
		else{
			int ans=s.query(x,y-1);
			if(ans>m)cout << -1 << '\n';
			else cout << ans << '\n';
		}
	}
}