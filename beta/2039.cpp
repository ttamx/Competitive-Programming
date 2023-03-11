#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> p2;

const int N=1e5+5;

struct fenwick{
    vector<p2> f;
    void resize(int n){
        f=vector<p2>(n+1,{0,0});
    }
    p2 sum(p2 a,p2 b){
        return {a.first+b.first,a.second+b.second};
    }
    void add(int i,p2 v){
        while(i<f.size())f[i]=sum(f[i],v),i+=i&-i;
    }
    p2 read(int i){
        p2 ret={0,0};
        while(i)ret=sum(ret,f[i]),i-=i&-i;
        return ret;
    }
    p2 lb(p2 v){
        int l=0,r=f.size()-1;
        while(l<r){
            int m=(l+r+1)/2;
            if(read(m)<=v)l=m;
            else r=m-1;
        }
        return read(l);
    }
}f;

int n,m;
int b[N],c[N],l[N],sz[N],pos[N];
vector<int> adj[N],used[N];
ll ans=0;

void dfs1(int u){
    sz[u]=1;
    for(auto v:adj[u])dfs1(v),sz[u]+=sz[v];
}

void dfs2(int u,bool del){
    int mxs=0,mxi=0;
    for(auto v:adj[u])if(sz[v]>mxs)mxs=sz[v],mxi=v;
    for(auto v:adj[u])if(v!=mxi)dfs2(v,1);
    if(mxi)dfs2(mxi,0),swap(used[u],used[mxi]);
    used[u].push_back(u),f.add(pos[u],{c[u],1});
    for(auto v:adj[u])if(v!=mxi)for(auto i:used[v])used[u].push_back(i),f.add(pos[i],{c[i],1});
    auto [x,y]=f.lb({m,n});
    ans=max(ans,1ll*l[u]*y);
    if(del)for(auto i:used[u])f.add(pos[i],{-c[i],-1});
    for(auto v:adj[u])used[v].clear();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    f.resize(n);
    int root=0;
    vector<p2> in;
    for(int i=1;i<=n;i++){
        cin >> b[i] >> c[i] >> l[i];
        in.push_back({c[i],i});
        if(b[i])adj[b[i]].push_back(i);
        else root=i;
    }
    sort(in.begin(),in.end());
    for(int i=0;i<n;i++)pos[in[i].second]=i+1;
    dfs1(root);
    dfs2(root,1);
    cout << ans;
}