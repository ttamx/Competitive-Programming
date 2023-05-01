#include<bits/stdc++.h>

using namespace std;

const int N=80005;

int n,cnt;
vector<pair<int,int>> adj[N];

int dfs(int u,int p,int val){
    int res=0;
    for(auto [v,w]:adj[u])if(v!=p){
        int d=w+dfs(v,u,val);
        if(d>=val)cnt++;
        else res+=d;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0,u,v,w;i<n;i++){
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    int rt;
    for(int i=0;i<=n;i++)if(adj[i].size()==1)rt=i;
    int l=0,r=1e9;
    while(l<r){
        int m=(l+r+1)/2;
        cnt=0;
        dfs(rt,rt,m);
        if(cnt>=3)l=m;
        else r=m-1;
    }
    cout << l;
}