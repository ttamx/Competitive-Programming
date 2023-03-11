#include<bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int> t3;

const int N=2e5;

int n,m;
int pa[N],l[N],r[N];
vector<t3> edge,mst,non;
vector<int> res[N];

int calc(int x,int y){
	return x*400+y;
}

int fp(int u){
	if(u==pa[u])return u;
	return pa[u]=fp(pa[u]);
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> m >> n;
	for(int i=0;i<m*2-1;++i){
		int x;
		if(i&1){
			for(int j=0;j<n;++j){
				cin >> x;
				edge.emplace_back(x,calc(i/2,j),calc(i/2+1,j));
			}
		}else{
			for(int j=0;j<n-1;++j){
				cin >> x;
				edge.emplace_back(x,calc(i/2,j),calc(i/2,j+1));
			}
		}
	}
	iota(pa,pa+N,0);
	sort(edge.begin(),edge.end());
	for(auto it:edge){
        int u=fp(get<1>(it));
        int v=fp(get<2>(it));
		if(u==v){
            non.emplace_back(it);
		}else{
		    mst.emplace_back(it);
            pa[u]=v;
		}
	}
	for(int i=0;i<non.size();++i)l[i]=0,r[i]=mst.size()-1;
	bool done;
	while(true){
        done=true;
        for(int i=0;i<non.size();++i){
            if(l[i]==r[i])continue;
            res[(l[i]+r[i]+1)/2].emplace_back(i);
            done=false;
        }
        if(done)break;
        iota(pa,pa+N,0);
        for(int i=0;i<mst.size();++i){
            for(auto j:res[i]){
                int u=fp(get<1>(non[j]));
                int v=fp(get<2>(non[j]));
                if(u==v)r[j]=i-1;
                else l[j]=i;
            }
            int u=fp(get<1>(mst[i]));
            int v=fp(get<2>(mst[i]));
            pa[u]=v;
            res[i].clear();
        }
	}
	int ans=2e9;
	for(int i=0;i<non.size();++i){
        ans=min(ans,get<0>(non[i])-get<0>(mst[l[i]]));
	}
	cout << ans;
}
