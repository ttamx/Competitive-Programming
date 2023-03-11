#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<int,int,int> t3;

const int N=2e5+5;

int n,m,q;
int pa[N],l[N],r[N];
p2 k[N];
t3 t[N];
vector<int> res[N];

int fp(int u){
	if(u==pa[u])return u;
	return pa[u]=fp(pa[u]);
}

struct node{
	int amx,lmx,rmx;
	void print(){
		cout << "(" << lmx << " " << amx << " " << rmx << ")";
	}
};

node merge(node a,node b){
	if(a.rmx==0)return b;
	if(b.lmx==0)return a;
	node c;
	c.amx=max({a.rmx,a.amx,b.amx,b.lmx});
	c.lmx=a.lmx;
	c.rmx=b.rmx;
	return c;
}

struct segtree{
	node tree[N*4];
	void build(int i,int ll,int rr){
		if(ll==rr){
			tree[i].amx=0;
			tree[i].lmx=l[ll-1];
			tree[i].rmx=l[ll];
			return;
		}
		int mm=(ll+rr)/2;
		build(i*2,ll,mm);
		build(i*2+1,mm+1,rr);
		tree[i]=merge(tree[i*2],tree[i*2+1]);
	}
	node query(int i,int ll,int rr,int ql,int qr){
		if(ll>qr||rr<ql)return {0,0,0};
		if(ql<=ll&&rr<=qr){
			return tree[i];
		}
		int mm=(ll+rr)/2;
		return merge(query(i*2,ll,mm,ql,qr),query(i*2+1,mm+1,rr,ql,qr));
	}
}s;

/*  l r m
1 : 1 2 2
2 : 3 3 2
3 : 6 6 5
4 : 3 3 2
5 : 4 5 5
*/

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
	s.build(1,1,n);
	for(int i=1;i<=q;++i){
		int x,y;
		cin >> x >> y;
		if(x==y)cout << 0 << '\n';
		else{
			int ans=s.query(1,1,n,x,y).amx;
			if(ans>m)cout << -1 << '\n';
			else cout << ans << '\n';
		}
	}
}