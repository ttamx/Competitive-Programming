#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int INF=1e9;

int n,q;
vector<int> adj[N],adj2[N];
int par[N],tin[N],tout[N],jump[N],dep[N];
int timer;
bool f[N];

void dfs(int u){
    tin[u]=++timer;
    for(auto v:adj[u]){
        if(v==par[u])continue;
        par[v]=u;
        dep[v]=dep[u]+1;
        jump[v]=dep[u]-dep[jump[u]]==dep[jump[u]]-dep[jump[jump[u]]]?jump[jump[u]]:u;
        dfs(v);
    }
    tout[u]=timer;
}

int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    while(dep[u]>dep[v])u=dep[jump[u]]>=dep[v]?jump[u]:par[u];
    while(u!=v){
        if(jump[u]!=jump[v])u=jump[u],v=jump[v];
        else u=par[u],v=par[v];
    }
    return u;
}

bool in_subtree(int u,int v){
    return tin[u]<=tin[v]&&tin[v]<=tout[u];
}

array<ll,2> solve(int u){
    array<ll,2> res={INF,INF};
    if(f[u])res[1]=0;
    ll sum=0,sum2=0,mn=INF;
    for(auto v:adj2[u]){
        auto e=solve(v);
        if(dep[v]-dep[u]>1)e[0]=min(e[0],e[1]+1);
        sum+=e[0];
        sum2+=min(e[0],e[1]);
        mn=min(mn,e[1]-e[0]);
    }
    if(f[u]){
        res[1]=sum;
    }else{
        res[0]=min(sum,sum2+1);
        res[1]=sum+mn;
    }
    adj2[u].clear();
    f[u]=false;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    par[1]=jump[1]=1;
    dfs(1);
    cin >> q;
    while(q--){
        int m;
        cin >> m;
        vector<int> a(m);
        for(auto &x:a){
            cin >> x;
            f[x]=true;
        }
        sort(a.begin(),a.end(),[&](int u,int v){return tin[u]<tin[v];});
        for(int i=1;i<m;i++)a.emplace_back(lca(a[i-1],a[i]));
        sort(a.begin(),a.end(),[&](int u,int v){return tin[u]<tin[v];});
        a.erase(unique(a.begin(),a.end()),a.end());
        m=a.size();
        vector<int> st{a[0]};
        for(int i=1;i<m;i++){
            int u=a[i];
            while(!in_subtree(st.back(),u))st.pop_back();
            adj2[st.back()].emplace_back(u);
            st.emplace_back(u);
        }
        auto e=solve(a[0]);
        ll ans=min(e[0],e[1]);
        cout << (ans<INF?ans:-1LL) << "\n";
    }
}