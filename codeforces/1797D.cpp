#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct node{
    int sz,fa;
    long long sum;
    set<pair<int,int>> ch;
}a[N];

int n,m;
vector<int> adj[N];

void dfs(int u,int p){
    a[u].sz=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        a[u].sz+=a[v].sz;
        a[u].sum+=a[v].sum;
        a[u].ch.emplace(-a[v].sz,v);
        a[v].fa=u;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i].sum;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    while(m--){
        int t,x;
        cin >> t >> x;
        if(t==1){
            cout << a[x].sum << '\n';
        }else{
            if(a[x].ch.empty())continue;
            int hv=a[x].ch.begin()->second;
            int fa=a[x].fa;
            a[x].ch.erase(a[x].ch.begin());
            a[fa].ch.erase({-a[x].sz,x});
            int sz=a[x].sz;
            long long sum=a[x].sum;
            a[x].sz-=a[hv].sz;
            a[hv].sz=sz;
            a[x].sum-=a[hv].sum;
            a[hv].sum=sum;
            a[x].fa=hv;
            a[hv].fa=fa;
            a[fa].ch.emplace(-a[hv].sz,hv);
            a[hv].ch.emplace(-a[x].sz,x);
        }
    }
}