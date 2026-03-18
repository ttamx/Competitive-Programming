#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(k);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int s,t;
    cin >> s >> t;
    s--,t--;
    if(find(a.begin(),a.end(),t)==a.end()){
        a.emplace_back(t);
    }
    auto check=[&](int mid){
        vector<int> fa(n);
        iota(fa.begin(),fa.end(),0);
        function<int(int)> fp=[&](int u){
            return fa[u]=u==fa[u]?u:fp(fa[u]);
        };
        vector<int> dist(n,-1),id(n,-1);
        queue<int> q;
        for(auto x:a){
            id[x]=x;
            dist[x]=0;
            q.emplace(x);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:adj[u]){
                if(id[v]==-1){
                    id[v]=id[u];
                    dist[v]=dist[u]+1;
                    q.emplace(v);
                }else if(dist[u]+dist[v]+1<=mid){
                    fa[fp(id[u])]=fp(id[v]);
                }
            }
        }
        return fp(s)==fp(t);
    };
    int l=1,r=n;
    while(l<r){
        int mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout << (l<n?l:-1) << "\n";
}