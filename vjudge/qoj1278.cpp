#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> dia(n),dep(n,-1);
    for(int i=0;i<n;i++){
        int m;
        cin >> m;
        vector<vector<int>> adj(m+2);
        for(int j=1;j<=m;j++){
            int p;
            cin >> p;
            adj[p].emplace_back(j);
            adj[j].emplace_back(p);
        }
        vector<int> d(m+2);
        function<void(int,int)> dfs=[&](int u,int p){
            for(auto v:adj[u])if(v!=p){
                d[v]=d[u]+1;
                dfs(v,u);
            }
        };
        d[0]=-1;
        dfs(0,-1);
        int rt=0;
        for(int j=1;j<=m;j++)if(d[j]>dep[i])dep[i]=d[j],rt=j;
        d[rt]=0;
        dfs(rt,-1);
        for(int j=1;j<=m;j++)dia[i]=max(dia[i],d[j]);
    };
    int sum=0;
    for(auto x:dep)sum+=x;
    int mn=1e9,mx=0;
    for(int i=0;i<n;i++){
        if(dep[i]==0)continue;
        int val=dia[i]+(sum-dep[i])*2;
        mn=min(mn,val);
        mx=max(mx,val);
    }
    mn=min(mn,mx);
    cout << mx << " " << mn << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}