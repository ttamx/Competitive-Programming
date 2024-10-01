#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> e(n);
    vector<int> a(n);
    for(int i=0;i<n;i++){
        int t;
        cin >> t;
        if(t==1){
            int x;
            cin >> x;
            e[i]={x,x};
        }else{
            cin >> e[i].first >> e[i].second;
        }
        e[i].first--,e[i].second--;
        cin >> a[i];
    }
    vector<int> p(m);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    };
    vector<bool> cyc(m);
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){return a[i]>a[j];});
    vector<vector<pair<int,int>>> adj(m);
    vector<int> roots;
    vector<int> match(m,-1);
    for(auto i:ord){
        auto [u,v]=e[i];
        if(fp(u)!=fp(v)){
            if(cyc[fp(u)]&&cyc[fp(v)]){
                continue;
            }
            adj[u].emplace_back(v,i);
            adj[v].emplace_back(u,i);
            if(cyc[fp(u)]){
                cyc[fp(v)]=true;
            }
            p[fp(u)]=fp(v);
        }else{
            if(cyc[fp(u)]){
                continue;
            }
            cyc[fp(u)]=true;
            match[u]=i;
            roots.emplace_back(u);
        }
    }
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto [v,i]:adj[u]){
            if(v==p){
                continue;
            }
            match[v]=i;
            dfs(v,u);
        }
    };
    for(auto x:roots){
        dfs(x,-1);
    }
    ll ans=0;
    for(auto x:match){
        if(x==-1){
            cout << -1;
            exit(0);
        }
        ans+=a[x];
    }
    cout << ans << "\n";
    for(auto x:match){
        cout << x+1 << " ";
    }
}