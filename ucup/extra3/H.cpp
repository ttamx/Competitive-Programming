#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int MOD=1e9+7;

mt19937_64 rng(9087410);

int n,m;
pair<int,int> edges[N];
vector<pair<int,int>> adj[N];
int tin[N],tout[N],dep[N],jump[N],par[N];
ll dist[N];
int timer=0;
vector<int> adj2[N];
bool mark[N];
uint64_t hsh[N];
vector<int> leaf;
int max_deg;
ll ans=0;
vector<int> nodes[N];
vector<pair<int,ll>> adj3[N];
int sz[N];

void dfs(int u){
    tin[u]=++timer;
    for(auto [v,w]:adj[u])if(v!=par[u]){
        dep[v]=dep[u]+1;
        par[v]=u;
        jump[v]=(dep[u]-dep[jump[u]]==dep[jump[u]]-dep[jump[jump[u]]]?jump[jump[u]]:u);
        dist[v]=dist[u]+w;
        dfs(v);
    }
    tout[u]=timer;
}

bool is_anc(int u,int v){
    return tin[u]<=tin[v]&&tin[v]<=tout[u];
}

int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    while(dep[u]>dep[v])u=(dep[jump[u]]>=dep[v]?jump[u]:par[u]);
    while(u!=v){
        if(jump[u]==jump[v])u=par[u],v=par[v];
        else u=jump[u],v=jump[v];
    }
    return u;
}

void dfs2(int u,uint64_t val,int p=0){
    max_deg=max(max_deg,(int)adj2[u].size()+p);
    if(mark[u]){
        hsh[u]^=val;
        if(!adj2[u].empty()){
            val=rng();
            hsh[u]^=val;
        }else{
            leaf.emplace_back(u);
        }
    }
    for(auto v:adj2[u]){
        dfs2(v,val,1);
    }
}

void dfs3(int u){
    for(auto [v,w]:adj[u])if(v!=par[u]){
        hsh[v]^=hsh[u];
        dfs3(v);
    }
}

inline void link(int u,int v){
    adj3[u].emplace_back(v,dist[v]-dist[u]);
}

void dfs4(int u,int tot){
    for(auto [v,w]:adj3[u]){
        dfs4(v,tot);
        sz[u]+=sz[v];
        ans=(ans+w%MOD*sz[v]%MOD*(tot-sz[v])%MOD)%MOD;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<n;i++){
        auto &[u,v]=edges[i];
        int w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    par[1]=jump[1]=1;
    dfs(1);
    for(int i=1;i<n;i++){
        auto &[u,v]=edges[i];
        if(dep[u]<dep[v])swap(u,v);
    }
    for(int i=0;i<m;i++){
        int k;
        cin >> k;
        if(!k)continue;
        vector<int> a(k);
        for(auto &x:a){
            cin >> x;
            x=edges[x].first;
            mark[x]=true;
        }
        sort(a.begin(),a.end(),[&](int u,int v){return tin[u]<tin[v];});
        a.erase(unique(a.begin(),a.end()),a.end());
        vector<int> st;
        auto b=a;
        for(auto u:a){
            int v=0;
            while(!st.empty()&&!is_anc(st.back(),u)){
                if(v)adj2[st.back()].emplace_back(v);
                v=st.back();
                st.pop_back();
            }
            if(v){
                int p=lca(u,v);
                adj2[p].emplace_back(v);
                if(p!=u&&(st.empty()||st.back()!=p)){
                    st.emplace_back(p);
                    b.emplace_back(p);
                }
            }
            st.emplace_back(u);
        }
        while(st.size()>1){
            int v=st.back();
            st.pop_back();
            adj2[st.back()].emplace_back(v);
        }
        max_deg=0;
        dfs2(st[0],0);
        if(max_deg>2){
            for(auto u:leaf)hsh[u]^=rng();
        }else{
            uint64_t val=rng();
            if(leaf.size()==1){
                hsh[1]^=val;
                hsh[st[0]]^=val;
                hsh[leaf[0]]^=val;
            }else{
                assert(leaf.size()==2);
                hsh[leaf[0]]^=val;
                hsh[leaf[1]]^=val;
            }
        }
        leaf.clear();
        for(auto x:b){
            mark[x]=false;
            adj2[x].clear();
        }
    }
    dfs3(1);
    vector<uint64_t> vals;
    for(int i=1;i<=n;i++)vals.emplace_back(hsh[i]);
    sort(vals.begin(),vals.end());
    for(int i=1;i<=n;i++){
        int idx=lower_bound(vals.begin(),vals.end(),hsh[i])-vals.begin();
        nodes[idx].emplace_back(i);
    }
    for(int i=0;i<n;i++){
        auto &a=nodes[i];
        if(a.empty())continue;
        for(auto x:a)sz[x]=1;
        sort(a.begin(),a.end(),[&](int u,int v){return tin[u]<tin[v];});
        a.erase(unique(a.begin(),a.end()),a.end());
        vector<int> st;
        auto b=a;
        for(auto u:a){
            int v=0;
            while(!st.empty()&&!is_anc(st.back(),u)){
                if(v)link(st.back(),v);
                v=st.back();
                st.pop_back();
            }
            if(v){
                int p=lca(u,v);
                link(p,v);
                if(p!=u&&(st.empty()||st.back()!=p)){
                    st.emplace_back(p);
                    b.emplace_back(p);
                }
            }
            st.emplace_back(u);
        }
        while(st.size()>1){
            int v=st.back();
            st.pop_back();
            link(st.back(),v);
        }
        dfs4(st[0],a.size());
        for(auto x:b){
            sz[x]=0;
            adj3[x].clear();
        }
    }
    cout << ans << "\n";
}