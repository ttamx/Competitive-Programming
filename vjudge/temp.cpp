#include<bits/stdc++.h>
using namespace std;
#define N 100020
typedef long long ll;
vector<pair<int,int> > G[N];
int n,m,Q;
class Basis{
public:
	int d[32];
	void Insert(int x){
		cerr << bitset<30>(x) << "\n";
		for(int i=29;i>=0;--i){
			if(x>>i&1){
				if(!d[i]){
					d[i]=x;
					for(int j=i-1;j>=0;--j){
						if(d[i]>>j&1){
							d[i]^=d[j];
						}
					}
					for(int j=i+1;j<30;++j){
						if(d[j]>>i&1){
							d[j]^=d[i];
						}
					}
					return;
				}
				else{
					x^=d[i];
				}
			}
		}
	}
}B;
int dfn[N],dis[N],num,sxor[N];
void dfs(int u){
	dfn[u]=++num;
	for(auto [v,w]:G[u]){
		if(!dfn[v]){
			dis[v]=dis[u]^w;
			dfs(v);
		}
		else if(dfn[u]>=dfn[v]){
			B.Insert(dis[u]^dis[v]^w);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>Q;
	for(int i=1;i<=m;++i){
		int u,v,w;
		cin>>u>>v>>w;
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
	}
	dfs(1);
    for(int i=0;i<30;i++)if(B.d[i])cerr << bitset<30>(B.d[i]) << " ";
	for(int i=1;i<=n;++i){
		sxor[i]=sxor[i-1]^dis[i];
	}
	while(Q--){
		int l,r;
		cin>>l>>r;
		int len=r-l+1;
		int w=sxor[r]^sxor[l-1];
		if(len&1)w=0;
		int ans=w;
		int t=(1LL*(r-l)*(r-l+1)/2)&1;
		for(int i=29;i>=0;--i){
			if((w>>i&1)!=t){
				ans^=B.d[i];
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
/*
101010100001100011001001100000
001011100110000011111011001001
101010100001100011001001100000
001011100110000011111011001001
001011010111001110100111101011
*/